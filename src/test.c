/** \file test.c
 *  \brief Ficheiro para teste do módulo
 * 
 *  Através do Unity, unit testing for C, são testadas as funções do módulo a implementar. Mais especificamente os ficheiros sensors.c e cmdproc.c. 
 * 
 *  \author Guilherme Santos, 103143
 *  \author Francisco Bastos, 103359
 *  \date 31/03/2025
*/

//#define UNITY_INCLUDE_DOUBLE 
#include "unity.h"
#include "sensors.h"
#include "cmdproc.h"

double expected_temp1[HISTORY_SIZE]={60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0};
double expected_temp2[HISTORY_SIZE]={-50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3};

double expected_hum1[HISTORY_SIZE] = {100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0};
double expected_hum2[HISTORY_SIZE] = {0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8};

int expected_co2_1[HISTORY_SIZE] = {20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400};
int expected_co2_2[HISTORY_SIZE] = {400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500};

int expected_reset[HISTORY_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

extern unsigned char UARTRxBuffer[UART_RX_SIZE];
extern unsigned char UARTTxBuffer[UART_TX_SIZE];
extern int rxBufLen;
extern int txBufLen;

const char expected_frame_A[] = "# A -39.3 5.8 2500 253 !\n";
const char expected_frame_Pt[] = "# P t -39.3 254 !\n";
const char expected_frame_Ph[] = "# P h 005.8 147 !\n";
const char expected_frame_Pc[] = "# P c 2500 186 !\n";
const char expected_frame_L[] = "# L +60.0 100.0 20000 218 !\n"
                                "# L +53.0 89.9 19000 197 !\n"
                                "# L +40.1 75.5 17500 134 !\n"
                                "# L +29.5 67.2 15000 136 !\n"
                                "# L +12.2 50.0 12500 117 !\n"
                                "# L 0.0 33.3 10000 018 !\n"
                                "# L -9.7 24.6 7500 045 !\n"
                                "# L -21.0 15.2 5000 069 !\n"
                                "# L -39.3 5.8 2500 040 !\n"
                                "# L -50.0 0.0 400 222 !\n";

const char expected_frame_R[] = "# R 0 162 !\n";


void setUp(void)
{
    // inicializar o buffer
    resetRxBuffer();
    resetTxBuffer();
   // reset_indices();
    return;
}

void tearDown(void)
{
    return;
}

void test_read_temperature(void)
{
    for (int i = (HISTORY_SIZE-1); i >= 0 ; i--)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_temp1[i], read_temperature());
    }
}

void test_read_humidity(void)
{
    for (int i = (HISTORY_SIZE-1); i >= 0 ; i--)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_hum1[i], read_humidity());
    }
}

void test_read_co2(void)
{
    for (int i = (HISTORY_SIZE-1); i >= 0 ; i--)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_co2_1[i], read_co2());
    }
}

void test_get_last_temp(void)
{
    double expected_temp[HISTORY_SIZE];
    get_last_temp_data(expected_temp);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_temp1[i], expected_temp[i]);
    }
    
    TEST_ASSERT_FLOAT_WITHIN(0.1, -50.0, read_temperature());
    get_last_temp_data(expected_temp);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.1, expected_temp2[i], expected_temp[i]);
    }
}

void test_get_last_hum(void)
{
    double expected_hum[HISTORY_SIZE];
    get_last_hum_data(expected_hum);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.01, expected_hum1[i], expected_hum[i]);
    }
    
    TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, read_humidity());
    get_last_hum_data(expected_hum);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.01, expected_hum2[i], expected_hum[i]);
    }
}

void test_get_last_co2(void)
{
    int expected_co2[HISTORY_SIZE];
    get_last_co2_data(expected_co2);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_co2_1, expected_co2, 20);
    }
    
    TEST_ASSERT_EQUAL_INT(400, read_co2());
    get_last_co2_data(expected_co2);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        TEST_ASSERT_EQUAL_INT_ARRAY(expected_co2_2, expected_co2, 20);;
    }
}

void test_history_reset(void)
{
    int reset_obtained[HISTORY_SIZE];
    history_reset(reset_obtained);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reset, reset_obtained, 20);
}

void teste_RX(void)
{

    int i, result;
    for (i = 0; i < UART_RX_SIZE; i++) {
        result = rxChar('A');
        TEST_ASSERT_EQUAL(0, result); 
    }

    result = rxChar('B');
    TEST_ASSERT_EQUAL(-1, result);

    resetRxBuffer();

    unsigned char atual[17];
    int len;


    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('P');
    rxChar(' ');
    rxChar('t');
    rxChar(' ');
    rxChar('+');
    rxChar('4');
    rxChar('6');
    rxChar(' ');
    rxChar('3');
    rxChar('4');
    rxChar('5');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    getRxBuffer(atual,&len);
    atual[len] = '\0'; 
    TEST_ASSERT_EQUAL_STRING("# P t +46 345 !\n", atual);
}

void teste_TX(void)
{
    resetTxBuffer();
    resetRxBuffer();

    unsigned char rx[17];
    unsigned char tx[17];
    int len;


    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('P');
    rxChar(' ');
    rxChar('t');
    rxChar(' ');
    rxChar('+');
    rxChar('4');
    rxChar('6');
    rxChar(' ');
    rxChar('3');
    rxChar('4');
    rxChar('5');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    getRxBuffer(rx,&len);
    rx[len] = '\0'; 
    TEST_ASSERT_EQUAL_STRING("# P t +46 345 !\n", rx);

    copyRxToTxBuffer(tx,&len);

    tx[len] = '\0'; 
    TEST_ASSERT_EQUAL_STRING(rx, tx);
}

void test_calc_checksum(void)
{
    unsigned char c = 'A';
    int checksum = calcChecksum(&c, 1);

    TEST_ASSERT_EQUAL_INT(65, checksum);

    unsigned char msg[] = "# P t +46 345 !\n";  // A sequência que queremos testar
    int checksum2 = calcChecksum(msg, 16);  // Calcula o checksum da sequência

    TEST_ASSERT_EQUAL_INT(227, checksum2);
}

void test_command_A(void)
{
    resetRxBuffer();
    resetTxBuffer();
    unsigned char tx[30];
    int return_actual,len;

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('A');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    return_actual = cmdProcessor();

    TEST_ASSERT_EQUAL_INT(0, return_actual);

    getTxBuffer(tx,&len); 

    tx[len] = '\0';
    TEST_ASSERT_EQUAL_STRING(expected_frame_A,tx);

}


void test_command_P_t(void)
{
    resetRxBuffer();
    resetTxBuffer();
    unsigned char tx[30];
    int len;

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('P');
    rxChar(' ');
    rxChar('t');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    cmdProcessor();


    getTxBuffer(tx,&len); 
    tx[len] = '\0';
    TEST_ASSERT_EQUAL_STRING(expected_frame_Pt,tx);

}

void test_command_P_h(void)
{
    resetRxBuffer();
    resetTxBuffer();
    unsigned char tx[30];
    int len;

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('P');
    rxChar(' ');
    rxChar('h');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    cmdProcessor();


    getTxBuffer(tx,&len); 
    tx[len] = '\0';
    TEST_ASSERT_EQUAL_STRING(expected_frame_Ph,tx);

}

void test_command_P_c(void)
{
    resetRxBuffer();
    resetTxBuffer();
    unsigned char tx[30];
    int len;

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('P');
    rxChar(' ');
    rxChar('c');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    cmdProcessor();


    getTxBuffer(tx,&len); 
    tx[len] = '\0';
    TEST_ASSERT_EQUAL_STRING(expected_frame_Pc,tx);

}

void test_command_P_k(void)
{
    resetRxBuffer();
    resetTxBuffer();

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('P');
    rxChar(' ');
    rxChar('k');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    int actual_return =  cmdProcessor();

    TEST_ASSERT_EQUAL_INT(-2,actual_return);


}

void test_command_L(void)
{
    resetRxBuffer();
    unsigned char tx[300];
    int len;

    int reset_obtained[HISTORY_SIZE];

    reset_indices();
    history_reset(reset_obtained);

    for (int i = 0; i < HISTORY_SIZE; i++) {
		read_temperature();
		read_humidity();
		read_co2();
	}

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('L');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    int actual_return =  cmdProcessor();
    

    TEST_ASSERT_EQUAL_INT(0,actual_return);
    getTxBuffer(tx,&len); 


    TEST_ASSERT_EQUAL_STRING(expected_frame_L,tx);

}

void test_command_R(void)
{
    resetRxBuffer();
    resetTxBuffer();
    unsigned char tx[256];
    int len;

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('R');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    cmdProcessor();
    
    getTxBuffer(tx,&len); 
    tx[len] = '\0';

    TEST_ASSERT_EQUAL_STRING(expected_frame_R,tx);

}

void test_command_X(void)
{

    resetRxBuffer();
    resetTxBuffer();

    rxChar(SOF_SYM);
    rxChar(' ');
    rxChar('X');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    int return_actual = cmdProcessor();


    TEST_ASSERT_EQUAL_INT(-2, return_actual);

}

void test_command_SOF(void)
{

    resetRxBuffer();
    resetTxBuffer();

    rxChar(' ');
    rxChar('X');
    rxChar(' ');
    rxChar(EOF_SYM);
    rxChar('\n');

    int return_actual = cmdProcessor();


    TEST_ASSERT_EQUAL_INT(-4, return_actual);

}

int main(void)
{
    UNITY_BEGIN();


    RUN_TEST(test_read_temperature);
    RUN_TEST(test_read_humidity);
    RUN_TEST(test_read_co2);
    RUN_TEST(test_get_last_temp);
    RUN_TEST(test_get_last_hum);
    RUN_TEST(test_get_last_co2);
    RUN_TEST(test_history_reset);

    RUN_TEST(teste_RX);
    RUN_TEST(teste_TX);
    RUN_TEST(test_calc_checksum);
    RUN_TEST(test_command_A);
    RUN_TEST(test_command_P_t);
    RUN_TEST(test_command_P_h);
    RUN_TEST(test_command_P_c);
    RUN_TEST(test_command_P_k);

    RUN_TEST(test_history_reset);
    RUN_TEST(test_command_L);


    RUN_TEST(test_command_R);
    RUN_TEST(test_command_X);
    RUN_TEST(test_command_SOF);

    return UNITY_END();
}