/** \file sensors.h
 *  \brief Funções do sensor inteligente
 * 
 *  O módulo a implementar é constituido por 2 partes. Neste ficheiro são definidas as funções da parte do sensor inteligente. Este sensor premite ler a temperatura (-50ºC ... 60ºC), a humidade relativa (0 ... 100%) e o CO2 (400 ... 20000 ppm).
 * 
 * \author Guilherme Santos, 103143
 * \date 26/03/2025
*/

#ifndef SENSORS_H
#define SENSORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DATA_SIZE 10
#define HISTORY_SIZE 20

/** \brief Ler a temperatura
 * 
 *  Leitura do valor da temperatura, a função lê o valor de tempratura guardado num array, e retorna esse mesmo valor. 
 * 
 *  \return Valor da temperatura
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
double read_temperature();

/** \brief Ler a humidade relativa
 * 
 *  Leitura do valor da humidade, a função lê o valor de humidade guardado num array, e retorna esse mesmo valor.
 * 
 *  \return Valor da humidade
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
double read_humidity();

/** \brief Ler os níveis de CO2
 * 
 *  Leitura do valor de CO2, a função lê o valor de CO2 guardado num array, e retorna esse mesmo valor.
 * 
 *  \return Valor de CO2
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
int read_co2();

/** \brief Retorno dos últimos 20 valores de temperatura
 * 
 *  A função coloca os últimos 20 valores de temperatura lidos num buffer passado à função. 
 * 
 *  \param[buffer] Array do histórico de valores da temperatura
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
void get_last_temp_data(double* buffer);

/** \brief Retorno dos últimos 20 valores de humidade
 * 
 *  A função coloca os últimos 20 valores de humidade lidos num buffer passado à função.
 * 
 *  \param[buffer] Array do histórico de valores da humidade
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
void get_last_hum_data(double* buffer);

/** \brief Retorno dos últimos 20 valores de CO2
 * 
 *  A função coloca os últimos 20 valores de CO2 lidos num buffer passado à função.
 * 
 *  \param[buffer] Array do histórico de valores de CO2
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
void get_last_co2_data(int* buffer);

/** \brief Limpeza do histórico
 * 
 *  A função faz a limpeza de um buffer, passado à função, apgando assim o histórico relativo a esse buffer.
 * 
 *  \param[buffer] Array do histórico a apagar
 *  \author Guilherme Santos, 103143
 *  \date 26/03/2025 
 */
void history_reset(int* buffer);

/** \brief Reset dos índices usados
 * 
 *  A função repõe os índices usados, nas funções implementadas, de volta à posição inicial.
 * 
 *  \author Francisco Bastos, 103359
 *  \date 07/04/2025 
 */
void reset_indices();

#endif // SENSORS_H

