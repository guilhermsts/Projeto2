/** \file sensors.c
 *  \brief ...
 * 
 *  Pequena introdução do ficheiro
 * 
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025
 */

#include <stdio.h>
#include "sensors.h"

double temp_data[DATA_SIZE] = {-50, -22.2, -5.2, 0, 13.8, 21.7, 29.6, 35.0, 46.2, 60};
double hum_data[DATA_SIZE] = {0, 5.8, 15.2, 24.6, 33.3, 50, 67.2, 75.5, 89.9, 100};
int co2_data[DATA_SIZE] = {400, 2500, 5000, 7500, 10000, 12500, 15000, 17500, 19000, 20000};
static int temp_index = 0;
static int hum_index = 0;
static int co2_index = 0;

double read_temperature();
{
    double value = temp_data[temp_index++];
    return value;
}

double read_humidity();
{
    double value = hum_data[hum_index++];
    return value;
}

int read_co2();
{
    double value = co2_data[co2_index++];
    return value;
}