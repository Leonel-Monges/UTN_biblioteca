/*
 * utn.c
 *
 *  Created on: 12 abr. 2022
 *      Author: Sistemas4
 */
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

static int getInt(int* pResultado);
static int esNumerica(char* cadena);

/**
 * @fn int utn_getInt(int*, char*, char*, int, int, int)
 * @brief Solicita un número entero al usuario y lo valida.
 *
 * @param pResultado: Puntero a entero donde se escribirá
 * 		  			  el valor ingresado en el caso de ser correcto.
 * @param mensaje: Puntero a cadena de caracteres con mensaje
 * 				   a imprimir antes de pedirle al usuario datos por consola.
 * @param mensajeError: Puntero a cadena de caracteres con mensaje de error
 * 						en el caso de que el dato ingresado no sea válido.
 * @param minimo: Valor mínimo admitido (inclusive).
 * @param maximo: Valor máximo admitido (inclusive).
 * @param reintentos: Cantidad de veces que se le volverá a pedir al usuario
 * 					  que ingrese un dato en caso de error.
 * @return 0 == OK || -1 == ERROR!
 */
int utn_getInt(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL
			&& minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 1)
			{
				if(bufferInt >= minimo && bufferInt <= maximo)
				{
					retorno = 0;
					*pResultado = bufferInt;
					break;
				}
				else
				{
					fflush(stdin);
					reintentos--;
					printf("%s", mensajeError);
				}
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**
 * @fn int utn_getFloat(float*, char*, char*, int, int, int)
 * @brief Solicita un número entero al usuario y lo valida.
 *
 * @param pResultado: Puntero a flotante donde se escribirá
 * 		  			  el valor ingresado en el caso de ser correcto.
 * @param mensaje: Puntero a cadena de caracteres con mensaje
 * 				   a imprimir antes de pedirle al usuario datos por consola.
 * @param mensajeError: Puntero a cadena de caracteres con mensaje de error
 * 						en el caso de que el dato ingresado no sea válido.
 * @param minimo: Valor mínimo admitido (inclusive).
 * @param maximo: Valor máximo admitido (inclusive).
 * @param reintentos: Cantidad de veces que se le volverá a pedir al usuario
 * 					  que ingrese un dato en caso de error.
 * @return 0 == OK || -1 == ERROR!
 */
int utn_getFloat(float *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL
			&& minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(scanf("%f", &bufferFloat) == 1)
			{
				if(bufferFloat >= minimo && bufferFloat <= maximo)
				{
					retorno = 0;
					*pResultado = bufferFloat;
					break;
				}
				else
				{
					fflush(stdin);
					reintentos--;
					printf("%s", mensajeError);
				}
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**
 * @fn int utn_getPorcentaje(float*, int, float, int)
 * @brief Realiza el incremento/decremento de un valor numerico,
 * 		  ingresando el porcentaje solicitado.
 *
 * @param pResultado: Puntero a flotante, con el valor a setear.
 * @param valorIngresado: Valor original a emplear.
 * @param porcentaje: Valor del porcentaje a emplear.
 * @param opcion: 0 para Incremento || 1 para Decremento.
 * @return 0 == OK || -1 == ERROR!
 */
int utn_getPorcentaje(float* pResultado, float valorIngresado, float porcentaje, int opcion)
{
	int retorno = -1;

	if(pResultado != NULL && valorIngresado > 0 && porcentaje > 0)
	{
		switch(opcion)
			{
				case 0:
					valorIngresado = valorIngresado + (valorIngresado * porcentaje);
					*pResultado = valorIngresado;
					retorno = 0;
					break;
				case 1:
					valorIngresado = valorIngresado - (valorIngresado * porcentaje);
					*pResultado = valorIngresado;
					retorno = 0;
					break;
			}
	}
	return retorno;
}

/**
 * @fn int utn_calcularOperacion(float*, float, float, int)
 * @brief Realiza la operacion matematica de 2 valores numericos,
 *		  contando con la seleccion de dicha operacion que el usuario estipule.
 *
 * @param pResultado: Puntero a flotante, con el valor de la operacion realizada a setear.
 * @param numero1: Primer valor numerico a pasar para dicha operacion.
 * @param numero2: Segundo valor numerico a pasar para dicha operacion.
 * @param operacion: Opciones a elegir para cada operacion (1-4)
 * 					1. + (Suma)
 *		  			2. - (Resta)
 *		  			3. * (Multiplicacion)
 *		  			4. / (Division)
 * @return 0 = OK || -1 = ERROR!
 */
int utn_calcularOperacion(float* pResultado, float numero1, float numero2, int opcionOperacion)
{
	int resultado = -1;
	float bufferResultado;

	if(pResultado != NULL && opcionOperacion > 0 && opcionOperacion <= 4)
	{
		switch(opcionOperacion)
		{
		case 1: // Suma
			bufferResultado = numero1 + numero2;
			*pResultado = bufferResultado;
			resultado = 0;
			break;
		case 2: // Resta
			bufferResultado = numero1 - numero2;
			*pResultado = bufferResultado;
			resultado = 0;
			break;
		case 3: // Multiplicacion
			bufferResultado = numero1 * numero2;
			*pResultado = bufferResultado;
			resultado = 0;
			break;
		case 4: // Division
			bufferResultado = numero1 / numero2;
			*pResultado = bufferResultado;
			resultado = 0;
			break;
		}
	}

	return resultado;
}

/**
 * @fn int getInt(int*)
 * @brief Obtiene el dato como una cadena de caracteres, para luego
 * 	      validarlo y parsear/formatear el dato a una variable entera.
 *
 * @param pResultado: Puntero a entero, con el valor a setear.
 * @return 1 == OK
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[64];

	scanf("%s",buffer);
	if(esNumerica(buffer)) // esNumerica(buffer) == 1
	{
		*pResultado = atoi(buffer);
		retorno = 1;
	}

	return retorno;
}

/**
 * @fn int esNumerica(char*)
 * @brief Recibe una cadena de caracteres y devuelve 1
 * 		  en el caso de que el texto este compuesto solo por números.
 *
 * @param cadena: Cadena de carateres a recorrer.
 * @return  1 == OK
 */
static int esNumerica(char* cadena)
{
	int retorno = -1;
	int i = 0;

	if(cadena != NULL)
	{
			while(cadena[i] != '\0')
			{
				if(cadena[i] < '0' || cadena[i] > '9')
				{
					break;
				}
				i++;
			}
			if(cadena[i] == '\0')
			{
				retorno = 1;
			}
	}

	return retorno;
}
