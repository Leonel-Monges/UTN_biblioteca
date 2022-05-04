/*
 * utn.c
 *
 *  Created on: 12 abr. 2022
 *      Author: Sistemas4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"

static int esNumerica(char* cadena);
static int esFlotante(char* cadena);
static int esLetra(char* caracter);
static int getInt(int* pResultado);
static int getFloat(float* pResultado);

/**
 * @fn int esNumerica(char*)
 * @brief Recibe una cadena de caracteres y devuelve 1
 * 		  en el caso de que el texto este compuesto solo por números.
 *
 * @param cadena: Cadena de caracteres a ser analizada.
 * @return 1 == OK/SI || 0 == ERROR!/NO
 */
static int esNumerica(char* cadena)
{
	int retorno = 0;
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

/**
 * @fn int esFlotante(char*)
 * @brief Verifica si la cadena/buffer son solo numeros flotantes
 *        (Se incluyen ejemplos como: 3.14 +3.14 -3.14 .314 +.314 -.314 314. +314. -314.)
 * @param cadena: Cadena de caracteres a ser analizada.
 * @return 1 == OK/SI || 0 == ERROR!/NO
 */
static int esFlotante(char* cadena)
{
	int retorno = 1; // Valor en OK!
	int i = 0;
	int contadorPuntos = 0; //No tiene que haber mas de 2 puntos.

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i = 0; cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0; // Valor en ERROR!
					break;
				}
			}
		}
	}
	return retorno;
}

/**
 * @fn int esLetra(char*)
 * @brief Verifica si la variable es una letra.
 *
 * @param caracter: Variable char a verificar.
 * @return 1 == OK/SI || 0 == ERROR!/NO
 */
static int esLetra(char* caracter)
{
	int respuesta = 1; // Valor en OK!

	if(	(*caracter < 'a' || *caracter > 'z') &&
		(*caracter < 'A' || *caracter > 'Z'))
	{
		respuesta = 0; // Valor en ERROR!
	}

	return respuesta;
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

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0'; // \n = \0

	if(esNumerica(buffer)) // esNumerica(buffer) == 1
	{
		*pResultado = atoi(buffer);
		retorno = 1;
	}

	return retorno;
}

/**
 * @fn int getFloat(float*)
 * @brief Obtiene el dato como una cadena de caracteres, para luego
 * 	      validarlo y parsear/formatear el dato a una variable flotante.
 *
 * @param pResultado: Puntero a entero, con el valor a setear.
 * @return 1 == OK
 */
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[64];

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0'; // \n = \0

	if(esFlotante(buffer)) // esFlotante(buffer) == 1
	{
		*pResultado = atof(buffer);
		retorno = 1;
	}

	return retorno;
}

// ---------------------------------------------------------------------------------------- //

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
			if(getFloat(&bufferFloat) == 1)
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
 * @fn int utn_getChar(char*, char*, char*, int)
 * @brief Solicita un caracter al usuario.
 *
 * @param pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @param mensaje: Es el mensaje a ser mostrado al usuario.
 * @param mensajeError: Es el mensaje de error a ser mostrado al usuario.
 * @param rangoInicial: Rango minimo de letras admitido.
 * @param rangoFinal: Rango maximo de letras admitido.
 * @param reintentos: Cantidad de oportunidades para ingresar el dato.
 * @return 0 == OK || -1 == ERROR!
 */
int utn_getChar(char* pResultado, char* mensaje, char* mensajeError, char rangoInicial, char rangoFinal, int reintentos)
{
	int retorno = -1;
	char bufferChar;

	if(		pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			rangoInicial <= rangoFinal &&
			reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			bufferChar = getchar();
			if(	esLetra(&bufferChar) == 1 &&
				bufferChar >= rangoInicial &&
				bufferChar <= rangoFinal)
			{
				retorno = 0;
				*pResultado = bufferChar;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
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


