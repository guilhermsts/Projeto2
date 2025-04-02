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
		
		switch(UARTRxBuffer[i+1]) { 
			
			case 'A':
				/* Read all real-time values */
				txChar('#');
				txChar('a');
				snprintf(checksum_str, sizeof(checksum_str), "%d", calcChecksum((unsigned char *)"A", 1));
				txChar(checksum_str[0]);
				txChar(checksum_str[1]);
				txChar(checksum_str[2]);
				txChar('!');
				break;

			case 'P':	
				// O sid está na posição i+2	
				sid = UARTRxBuffer[i+2]; 

				/* Check sensor type */
                if (sid == 't') {
                    sensor_value = (int)read_temperature();
                    sensor_type = 't';
                } else if (sid == 'h') {
                    sensor_value = (int)read_humidity();
                    sensor_type = 'h';
                } else if (sid == 'c') {
                    sensor_value = read_co2();
                    sensor_type = 'c';
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
			
                /* Send response */
                txChar('#');
                txChar('p');
                txChar(sensor_type);
                txChar('+');
                txChar((sensor_value / 10) + '0');
                txChar((sensor_value % 10) + '0');
                txChar(checksum_str[0]);
                txChar(checksum_str[1]);
                txChar(checksum_str[2]);
                txChar('!');
				txChar('!');
				
				break;
					
			case 'L':
                /* Retrieve last 20 samples */
                get_last_temp_data(temp_buffer);
                get_last_hum_data(hum_buffer);
                get_last_co2_data(co2_buffer);
                txChar('#');
                txChar('l');
                snprintf(checksum_str, sizeof(checksum_str), "%d", calcChecksum((unsigned char *)"L", 1));
                txChar(checksum_str[0]);
                txChar(checksum_str[1]);
                txChar(checksum_str[2]);
                txChar('!');
                break;

			case 'R':
                /* Reset history */
                history_reset((int*)temp_buffer);
                history_reset((int*)hum_buffer);
                history_reset(co2_buffer);
                txChar('#');
                txChar('r');
                snprintf(checksum_str, sizeof(checksum_str), "%d", calcChecksum((unsigned char *)"R", 1));
                txChar(checksum_str[0]);
                txChar(checksum_str[1]);
                txChar(checksum_str[2]);
                txChar('!');
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
	/* Here you are supposed to compute the modulo 256 checksum */
	/* of the first n bytes of buf. Then you should convert the */
	/* checksum to ascii (3 digitas/chars) and compare each one */
	/* of these digits/characters to the ones in the RxBuffer,	*/
	/* positions nbytes, nbytes + 1 and nbytes +2. 				*/
	
	/* That is your work to do. In this example I just assume 	*/
	/* that the checksum is always OK.							*/	

	int checksum = 0;
    char checksum_str[4];
    
    // Calcula a soma módulo 256 dos primeiros n bytes
    for (int i = 0; i < nbytes; i++) {
        checksum += buf[i];
    }
    checksum %= 256; // Garantir que está no intervalo de um byte
    
    // Converte o checksum para ASCII (3 dígitos)
    snprintf(checksum_str, sizeof(checksum_str), "%03d", checksum);
    
    // Compara os caracteres gerados com os armazenados no RX buffer
    if (checksum_str[0] != UARTRxBuffer[nbytes] ||
        checksum_str[1] != UARTRxBuffer[nbytes + 1] ||
        checksum_str[2] != UARTRxBuffer[nbytes + 2]) {
        return 0; // Checksum inválido
    }
    
    return 1; // Checksum válido		
}

/*
 * rxChar
 */
int rxChar(unsigned char car)
{

	/* If rxbuff not full add char to it */
	if (rxBufLen < UART_RX_SIZE) {
		UARTRxBuffer[rxBufLen] = car;
		rxBufLen += 1;
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

	/* If rxbuff not full add char to it */
	if (txBufLen < UART_TX_SIZE) {
		UARTTxBuffer[txBufLen] = car;
		txBufLen ++;
		return 0;		
	}	
	/* If cmd string full return error */
	return -1;
}

/*
 * resetRxBuffer
 */
void resetRxBuffer(void)
{
	rxBufLen = 0;		
	return;
}

/*
 * resetTxBuffer
 */
void resetTxBuffer(void)
{
	txBufLen = 0;		
	return;
}

/*
 * getTxBuffer
 */
void getTxBuffer(unsigned char * buf, int * len)
{
	*len = txBufLen;
	if(txBufLen > 0) {
		memcpy(buf,UARTTxBuffer,*len);
	}	
	
	return;
}


