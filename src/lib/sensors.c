/** \file sensors.c
 *  \brief Implementação das funções do sensor inteligente
 * 
 *  Implementação das funções necessárias para o sensor realizar os comandos a receber da uart.
 * 
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025
 */

#include <stdio.h>
#include "sensors.h"

double temp_data[DATA_SIZE] = {-50.0, -39.3, -21.0, -9.7, 0.0, 12.2, 29.5, 40.1, 53.0, 60.0};
double hum_data[DATA_SIZE] = {0.0, 5.8, 15.2, 24.6, 33.3, 50.0, 67.2, 75.5, 89.9, 100.0};
int co2_data[DATA_SIZE] = {400, 2500, 5000, 7500, 10000, 12500, 15000, 17500, 19000, 20000};

double temp_history[HISTORY_SIZE];
double hum_history[HISTORY_SIZE];
int co2_history[HISTORY_SIZE];

static int temp_data_index = 0;
static int temp_history_index = 0;

static int hum_data_index = 0;
static int hum_history_index = 0;

static int c02_data_index = 0;
static int co2_history_index = 0;

double read_temperature()
{
    double value = temp_data[temp_data_index++];
    temp_history[temp_history_index++] = value;

    if (temp_data_index >= DATA_SIZE)
    {
        temp_data_index = 0;
    }
    
    if (temp_history_index >= HISTORY_SIZE)
    {
        temp_history_index = 0;
    }

    return value;
}

double read_humidity()
{
    double value = hum_data[hum_data_index++];
    hum_history[hum_history_index++] = value;

    if (hum_data_index >= DATA_SIZE)
    {
        hum_data_index = 0;
    }
    
    if (hum_history_index >= HISTORY_SIZE)
    {
        hum_history_index = 0;
    }

    return value;
}

int read_co2()
{

    int value = co2_data[c02_data_index++];

    co2_history[co2_history_index++] = value;
    
    if (c02_data_index >= DATA_SIZE)
    {
        c02_data_index = 0;
    }
    
    if (co2_history_index >= HISTORY_SIZE)
    {
        co2_history_index = 0;
    }

    return value;
}

void get_last_temp_data(double* buffer)
{
    int index = (temp_history_index == 0) ? (HISTORY_SIZE - 1) : (temp_history_index - 1);
    
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
       buffer[i] = temp_history[index];

       if (index == 0)
       {
            index = HISTORY_SIZE - 1;
       }
       else
       {
            index--;
       }
    }
}

void get_last_hum_data(double* buffer)
{
    int index = (hum_history_index == 0) ? (HISTORY_SIZE - 1) : (hum_history_index - 1);
    
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
       buffer[i] = hum_history[index];

       if (index == 0)
       {
            index = HISTORY_SIZE - 1;
       }
       else
       {
            index--;
       }
    }
}

void get_last_co2_data(int* buffer)
{
    int index = (co2_history_index == 0) ? (HISTORY_SIZE - 1) : (co2_history_index - 1);

    for (int i = 0; i < HISTORY_SIZE; i++)
    {
       buffer[i] = co2_history[index];

       if (index == 0)
       {
            index = HISTORY_SIZE - 1;
       }
       else
       {
            index--;
       }
    }
}

void history_reset(int* buffer)
{
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        buffer[i] = 0;
    }
}

void reset_indices()
{
    temp_data_index = 0;
    temp_history_index = 0;

    hum_data_index = 0;
    hum_history_index = 0;

    c02_data_index = 0;
    co2_history_index = 0;
}