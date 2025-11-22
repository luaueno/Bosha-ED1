#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * @file estilo_texto.h
 * @brief Interface para gerenciamento de estilos de texto.
 */

#include <stdlib.h>

/**
 * @brief Tipo opaco para o estilo de texto.
 */
typedef void* ESTILOTEXTO;

/**
 * @brief Cria um novo EstiloTexto.
 *
 * @param ff Font family.
 * @param fw Font weight ("bold", "normal"...)
 * @param fs Font size.
 *
 * @return ESTILOTEXTO, ou NULL se falhar.
 */
ESTILOTEXTO criaEstiloTexto(char* ff, char* fw, int fs);

/**
 * @brief Libera um EstiloTexto.
 */
void desalocaEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna a font family.
 */
char* getFFEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna o font weight.
 */
char* getFWEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna o font size.
 */
int getFSEstiloTexto(ESTILOTEXTO estilo);

#endif
