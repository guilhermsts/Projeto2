/** \file sensors.h
 *  \brief ...
 * 
 *  Pequena introdução 
 * 
 * \author Guilherme Santos, 103143
 * \date 26/03/2025
*/

#ifndef SENSORS_H
#define SENSORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DATA_SIZE 20
#define HISTORY_SIZE 20

double read_temperature();
double read_humidity();
int read_co2();

#endif // SENSORS_H

