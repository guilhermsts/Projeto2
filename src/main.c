/** \file main.c
 *  \brief Ficheiro de simulação do projeto 2
 * 
 *  São feitos alguns testes às funções implementadas e é simulado o projeto a implementar. De notar que aqui é só suposto ter uma visão e resultados finais do projeto.
 *  Para testar as funções uma a uma foi feito um ficheiro unity.c. 
 * 
 *  \author Francisco Bastos, 103359
 *  \date 06/04/2025
 */

/* ******************************************************/
/* SETR 23/24, Paulo Pedreiras                          */
/* 		Sample code for Assignment 2					*/
/*   	A few tests to the cmdProcessor to illustrate	*/
/*      how the the tests can be carried out.         	*/
/*														*/
/* Note that I'm not using Unity! That is part of your 	*/
/*		work. 											*/
/*                                                      */
/* Compile with: gcc cmdproc.c main.c -o main           */
/*	Feel free to use flags such as -Wall -Wpedantic ...	*/
/*	and it is a good idea to create a makefile			*/
/*                                                      */
/* ******************************************************/
#include <stdio.h>
#include <string.h>
#include "cmdproc.h"
#include "sensors.h"

int main(void) 
{
	int  err;
	int len,i;
	unsigned char ans[30]; 
	unsigned char ansTest1[]={'#',' ','P',' ','t', ' ', '0','.','0',' ','1', '4', '6', ' ','!','\n'};
	
	printf("\n Smart Sensor interface emulation \n");
	printf(" \t - simple illustration of interface and use \n\n\r");
	
	/* Init UART RX and TX buffers */
	resetTxBuffer();
	resetRxBuffer();
	
	/* Test 1 */
	
	printf("Test1 - check the answer to a valid Pt command\n");
	
	/* 1 - send the command */
	rxChar('#');
	rxChar(' ');
	rxChar('P');
	rxChar(' ');
	rxChar('t');
	rxChar(' ');
	rxChar('1');
	rxChar('9');
	rxChar('6');
	rxChar('!');
			
	/* 2 - Process the comand and check the answer */
	
	cmdProcessor();

	getTxBuffer(ans, &len);

	 /*You can print the answer to see what is wrong, if necessary */
	printf("\t Received answer: ");
	
		for (i = 0; i < len; i++) {
			printf("%c", ans[i]);
		}

	printf("\n\t Expected answer: ");
	for (i = 0; i < sizeof(ansTest1); i++) {
		printf("%c", ansTest1[i]);
	}
	printf("\n");

	if(memcmp(ans,ansTest1,len)) {
		printf(" \nTest 1 failed\n");
	} else {
		printf("\nTest 1 succeeded\n");
	}	
	
	
	/* Test 2 */
	resetRxBuffer();
	printf("Test2 - check the answer to a transmission omission/error \n");
	
	/* 1 - send the command */
	rxChar('#');
	rxChar(' ');
	rxChar('P');
	rxChar(' ');
	// rxChar('t'); - simulates missing character, emulates a tx error 
	rxChar('1');
	rxChar('9');
	rxChar('6');
	rxChar(' ');
	rxChar('!');
	rxChar('\n');
			
	/* 2 - Process the comand and check the answer */
	
	err = cmdProcessor();
		
	if(err == -2) {
		printf("Test 2 succeeded, as omission was detected\n");
	} else {
		printf("Test 2 failed, as omission was not detected\n");
	}		
	
	/* Much more tests are needed. Unity shoul be used for it. */

	return 0;
}
