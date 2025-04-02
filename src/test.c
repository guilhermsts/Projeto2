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

double expected_temp1[HISTORY_SIZE]={60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0};
double expected_temp2[HISTORY_SIZE]={-50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3};

double expected_hum1[HISTORY_SIZE] = {100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0};
double expected_hum2[HISTORY_SIZE] = {0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8};

int expected_co2_1[HISTORY_SIZE] = {20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400};
int expected_co2_2[HISTORY_SIZE] = {400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500};

int expected_reset[HISTORY_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setUp(void)
{
    // inicializar o buffer
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

    return UNITY_END();
}