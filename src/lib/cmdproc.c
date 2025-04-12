/** \file cmdproc.c
 *  \brief Implementação do módulo de processamento de comandos recebidos via UART.
 * 
 *  No ficheiro são implemenatdas as funções para o processamento de comandos recebidos via UART e tratar dados de um sensor inteligente.
 *  Foi desenvolvido à parte um módulo para o sensor inteligente, sendo usado valores e funções aí desenvolvidos. 
 * 
 *  \author Francisco Bastos, 103359
 *  \date 06/04/2025
 */

/* ****************************** */
/* See cmdProc.h for indications  */
/* ****************************** */
#include <stdio.h>
#include <string.h>

#include "cmdproc.h"
#include "sensors.h"

/* Internal variables */
/* Used as part of the UART emulation */
static unsigned char UARTRxBuffer[UART_RX_SIZE];
static unsigned char rxBufLen = 0; 

static unsigned char UARTTxBuffer[UART_TX_SIZE];
static unsigned char txBufLen = 0; 

 
/* Function implementation */

/* 
 * cmdProcessor
 */ 
int cmdProcessor(void)
{
	int i;
	unsigned char sid;
	int sensor_value;
    char sensor_type;
    char checksum_str[4];
    double temp_buffer[HISTORY_SIZE];
    double hum_buffer[HISTORY_SIZE];
    int co2_buffer[HISTORY_SIZE];

	/* Detect empty cmd string */
	if(rxBufLen == 0)
		return -1; 
	
	/* Find index of SOF */
	for(i=0; i < rxBufLen; i++) {
		if(UARTRxBuffer[i] == SOF_SYM) {
			break;
		}
	}
	

	/* If a SOF was found look for commands */
	if(i < rxBufLen) {
		
		switch(UARTRxBuffer[i+2]) { 

			case 'A':
                double temperature = read_temperature();
                double humidity = read_humidity();
                int co2 = read_co2();
            
                char response[64];
                char final_response[64];

                snprintf(response, sizeof(response), "A %.1f %.1f %d", temperature, humidity, co2);
                int checksum = calcChecksum((unsigned char *)response, strlen(response));

                snprintf(final_response, sizeof(final_response), "# A %.1f %.1f %d %03d", temperature, humidity, co2, checksum);

                for (int i = 0; final_response[i] != '\0'; i++) {
                    txChar(final_response[i]);
                }
                txChar(' ');
                txChar(EOF_SYM);
                txChar('\n');

                break;

			case 'P':	
            
                char response1[64];
                char final_response1[64];
				// O sid está na posição i+4	
				sid = UARTRxBuffer[i+4]; 

				/* Check sensor type */
                if (sid == 't') {
                    sensor_value = (int)read_temperature();
                    sensor_type = 't';
                    snprintf(response1, sizeof(response1), "P %c %.1f", sensor_type,temperature);
                    int checksumP = calcChecksum((unsigned char *)response1, strlen(response1));
                    snprintf(final_response1, sizeof(final_response1), "# P %c %.1f %03d", sensor_type,temperature, checksumP);
                    for (int i = 0; final_response1[i] != '\0'; i++) {
                        txChar(final_response1[i]);
                    }
                                
                    txChar(' ');
                    txChar(EOF_SYM);
                    txChar('\n');

                } else if (sid == 'h') {
                    sensor_value = (int)read_humidity();
                    sensor_type = 'h';
                    snprintf(response1, sizeof(response1), "P %c %.1f", sensor_type,humidity);
                    int checksumP = calcChecksum((unsigned char *)response1, strlen(response1));
                    snprintf(final_response1, sizeof(final_response1), "# P %c %05.1f %03d", sensor_type, humidity, checksumP);
                    for (int i = 0; final_response1[i] != '\0'; i++) {
                        txChar(final_response1[i]);
                    }
                                
                    txChar(' ');
                    txChar(EOF_SYM);
                    txChar('\n');

                } else if (sid == 'c') {
                    sensor_value = read_co2();
                    sensor_type = 'c';
                    snprintf(response1, sizeof(response1), "P %c %d", sensor_type,co2);
                    int checksumP = calcChecksum((unsigned char *)response1, strlen(response1));
                    snprintf(final_response1, sizeof(final_response1), "# P %c %d %03d", sensor_type, co2, checksumP);
                    for (int i = 0; final_response1[i] != '\0'; i++) {
                        txChar(final_response1[i]);
                    }
                                
                    txChar(' ');
                    txChar(EOF_SYM);
                    txChar('\n');
                } else {
                    return -2; /* Invalid sensor type */
                }
				
				/* Check checksum */
				if(!(calcChecksum(&(UARTRxBuffer[i+1]),2))) {
					return -3;
				}
				
				/* Check EOF */
				if(UARTRxBuffer[i+6] != EOF_SYM) {
					return -4;
				}
	
				break;
					
			case 'L':
                char response2[300];
                char final_response2[300];
                int len = 0;

                memset(response2, 0, sizeof(response2));
                memset(final_response2, 0, sizeof(final_response2));

                /* Retrieve last 20 samples */
                get_last_temp_data(temp_buffer);
                get_last_hum_data(hum_buffer);
                get_last_co2_data(co2_buffer);

                for (int i = 0; i < HISTORY_SIZE; i++) {
                    printf("LEITURA %d: temp_buffer[%d] = %.1f, hum_buffer[%d] = %.1f, co2_buffer[%d] = %d\n", 
                            i+1,i, temp_buffer[i], i, hum_buffer[i], i, co2_buffer[i]);
                }


                for (int i = 0; i < 10; i++) {
                    if( temp_buffer[i] > 0 )
                        snprintf(response2, sizeof(response2), "L +%.1f %.1f %d ", temp_buffer[i], hum_buffer[i], co2_buffer[i]);
                    else
                        snprintf(response2, sizeof(response2), "L %.1f %.1f %d ", temp_buffer[i], hum_buffer[i], co2_buffer[i]);

                    int checksumL = calcChecksum((unsigned char *)response2, strlen(response2));

                    if( temp_buffer[i] > 0 )
                        snprintf(final_response2, sizeof(final_response2), "# L +%.1f %.1f %d %03d", temp_buffer[i], hum_buffer[i], co2_buffer[i], checksumL);
                    else
                        snprintf(final_response2, sizeof(final_response2), "# L %.1f %.1f %d %03d", temp_buffer[i], hum_buffer[i], co2_buffer[i], checksumL);

                    for (int i = 0; final_response2[i] != '\0'; i++) {
                        txChar(final_response2[i]);
                    }
                    txChar(' ');  
                    txChar(EOF_SYM);
                    txChar('\n');
                }

                break;

			case 'R':
                char response3[256];
                char final_response3[256];

                /* Reset history */
                history_reset((int*)temp_buffer);
                history_reset((int*)hum_buffer);
                history_reset(co2_buffer);

                snprintf(response3, sizeof(response3), "R 0");
                int checksumR = calcChecksum((unsigned char *)response3, strlen(response3));
                snprintf(final_response3, sizeof(final_response3), "# R 0 %03d", checksumR);
                for (int i = 0; final_response3[i] != '\0'; i++) {
                    txChar(final_response3[i]);
                }

                txChar(' ');  
                txChar(EOF_SYM);
                txChar('\n');
                break;

			default:
				/* If code reaches this place, the command is not recognized */
				return -2;				
		}

		/* Remove processed command from buffer */
		memmove(UARTRxBuffer, UARTRxBuffer + i + 7, rxBufLen - (i + 7));
        rxBufLen -= (i + 7);
		return 0;
	}
	
	/* Cmd string not null and SOF not found */
	return -4;

}

/* 
 * calcChecksum
 */ 
int calcChecksum(unsigned char * buf, int nbytes) {

	int checksum = 0;
    char checksum_str[6];
    
    // Calcula a soma módulo 256 dos primeiros n bytes
    for (int i = 0; i < nbytes; i++) {
        checksum += buf[i];
    }
    checksum %= 256; // Garantir que está no intervalo de um byte
    
	return checksum;	
}

/*
 * rxChar
 */
int rxChar(unsigned char car)
{

	/* If rxbuff not full add char to it */
	if (rxBufLen < UART_RX_SIZE) {
		UARTRxBuffer[rxBufLen] = car;
		rxBufLen ++;
		return 0;		
	}	
	/* If cmd string full return error */
	return -1;
}

/*
 * txChar
 */
int txChar(unsigned char car)
{
	if (txBufLen < UART_TX_SIZE) {
        UARTTxBuffer[txBufLen] = car;
        txBufLen ++;
        return 0;
    } else {
        // Log de erro ou mensagem para depuração
        printf("Erro: Buffer de transmissão cheio!\n");
        return -1;
    }
}

/*
 * resetRxBuffer
 */
void resetRxBuffer(void)
{
	memset(UARTRxBuffer, 0, UART_RX_SIZE); 
    rxBufLen = 0;	
	return;
}

/*
 * resetTxBuffer
 */
void resetTxBuffer(void)
{
	memset(UARTTxBuffer, 0, UART_TX_SIZE); 
    txBufLen = 0;	
	return;
}

/*
 * getTxBuffer
 */
void getTxBuffer(unsigned char * buf, int * len)
{
    if (txBufLen > 0) {
        memcpy(buf, UARTTxBuffer, txBufLen);
        *len = txBufLen;
        buf[*len] = '\0';
    } else {
        *len = 0;
        printf("txBuffer está vazio.\n");
    }
	
	return;
}


/*
 * getRxBuffer
 */
void getRxBuffer(unsigned char *buf, int *len) {

    *len = rxBufLen;
    if (rxBufLen > 0) {
        memcpy(buf, UARTRxBuffer, rxBufLen); 
    }
	return;
}

void copyRxToTxBuffer(unsigned char *buf, int *len) {
    if (rxBufLen > 0) {
        memcpy(UARTTxBuffer, UARTRxBuffer, rxBufLen); 
		memcpy(buf, UARTTxBuffer, rxBufLen); 
        *len = rxBufLen;  
    } else {
        *len = 0;  
    }
}
