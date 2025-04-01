/** \file test.c
 *  \brief ...
 * 
 *  ...
 * 
 *  \author Guilherme Santos, 103143
 *  \author Francisco Bastos, 103359
 *  \date 31/03/2025
*/

#include "unity.h"
#include "sensors.h"

double expected_temp1[DATA_SIZE]={60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0};
double expected_temp2[DATA_SIZE]={-50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3, -50.0, 60.0, 53.0, 40.1, 29.5, 12.2, 0.0, -9.7, -21.0, -39.3};
double expected_temp[DATA_SIZE];

double expected_hum1[DATA_SIZE] = {100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0};
double expected_hum2[DATA_SIZE] = {0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8, 0.0, 100.0, 89.9, 75.5, 67.2, 50.0, 33.3, 24.6, 15.2, 5.8};
double expected_hum[DATA_SIZE];

int expected_co2_1[DATA_SIZE] = {20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400};
int expected_co2_2[DATA_SIZE] = {400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500, 400, 20000, 19000, 17500, 15000, 12500, 10000, 7500, 5000, 2500};
int expected_co2[DATA_SIZE];

int expected_reset[DATA_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int reset_obtained[DATA_SIZE];

void test_read_temperature(void)
{
    TEST_ASSERT_EQUAL_DOUBLE(-50.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-39.3, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-21.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-9.7, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(0.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(12.2, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(29.5, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(40.1, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(53.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(60.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-50.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-39.3, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-21.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(-9.7, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(0.0 ,read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(12.2, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(29.5, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(40.1, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(53.0, read_temperature());
    TEST_ASSERT_EQUAL_DOUBLE(60.0, read_temperature());
}

void test_read_humidity(void)
{
    TEST_ASSERT_EQUAL_DOUBLE(0.0, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(5.8, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(15.2, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(24.6, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(33.3, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(50.0, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(67.2, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(75.5, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(89.9, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(100.0, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(0.0, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(5.8, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(15.2, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(24.6, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(33.3, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(50.0, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(67.2, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(75.5, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(89.9, read_humidity());
    TEST_ASSERT_EQUAL_DOUBLE(100.0, read_humidity());
}

void test_read_co2(void)
{
    TEST_ASSERT_EQUAL_INT(400, read_co2());
    TEST_ASSERT_EQUAL_INT(2500, read_co2());
    TEST_ASSERT_EQUAL_INT(5000, read_co2());
    TEST_ASSERT_EQUAL_INT(7500, read_co2());
    TEST_ASSERT_EQUAL_INT(10000, read_co2());
    TEST_ASSERT_EQUAL_INT(12500, read_co2());
    TEST_ASSERT_EQUAL_INT(15000, read_co2());
    TEST_ASSERT_EQUAL_INT(17500, read_co2());
    TEST_ASSERT_EQUAL_INT(19000, read_co2());
    TEST_ASSERT_EQUAL_INT(20000, read_co2());
    TEST_ASSERT_EQUAL_INT(400, read_co2());
    TEST_ASSERT_EQUAL_INT(2500, read_co2());
    TEST_ASSERT_EQUAL_INT(5000, read_co2());
    TEST_ASSERT_EQUAL_INT(7500, read_co2());
    TEST_ASSERT_EQUAL_INT(10000, read_co2());
    TEST_ASSERT_EQUAL_INT(12500, read_co2());
    TEST_ASSERT_EQUAL_INT(15000, read_co2());
    TEST_ASSERT_EQUAL_INT(17500, read_co2());
    TEST_ASSERT_EQUAL_INT(19000, read_co2());
    TEST_ASSERT_EQUAL_INT(20000, read_co2());
}

void test_get_last_temp(void)
{
    
    get_last_temp_data(*expected_temp);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected_temp1, expected_temp);
    TEST_ASSERT_EQUAL_DOUBLE(-50.0,read_temperature());
    get_last_temp_data(*expected_temp);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected_temp2, expected_temp);
}

void test_get_last_hum(void)
{
    get_last_hum_data(*expected_hum);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected_hum1, expected_hum);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, read_humidity());
    get_last_hum_data(*expected_hum);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected_hum2, expected_hum);
}

void test_get_last_co2(void)
{
    get_last_co2_data(*expected_co2);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_co2_1, expected_co2);
    TEST_ASSERT_EQUAL_INT(400, read_co2());
    get_last_co2_data(*expected_co2);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_co2_2, expected_co2);
}

void test_history_reset(void)
{
    history_reset(*reset_obtained);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reset, reset_obtained);
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