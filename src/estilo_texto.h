#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * @file estilo_texto.h
 * @brief Interface para gerenciamento de estilos de texto.
 *
 * Esta interface define funções para criação, acesso e destruição
 * de objetos que armazenam propriedades de estilo de texto, como:
 * - ff: font family
 * - fw: font weight
 * - fs: font size
 *
 * A estrutura interna é opaca e definida apenas no .c.
 */

#include <stdlib.h>

/**
 * @brief Tipo opaco que representa um estilo de texto.
 */
typedef void* ESTILOTEXTO;

/**
 * @brief Cria um novo objeto EstiloTexto.
 *
 * @param ff Font family.
 * @param fw Font weight ("normal", "bold", etc).
 * @param fs Font size.
 *
 * @return ESTILOTEXTO Ponteiro opaco para o objeto criado, ou NULL em caso de erro.
 */
ESTILOTEXTO criaEstiloTexto(char* ff, char* fw, int fs);

/**
 * @brief Libera toda a memória associada a um EstiloTexto.
 *
 * @param estilo Objeto criado por criaEstiloTexto.
 */
void desalocaEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna a font family.
 *
 * @param estilo Objeto EstiloTexto.
 * @return char* Font family, ou NULL se estilo for inválido.
 */
char* getFFEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna a font weight.
 *
 * @param estilo Objeto EstiloTexto.
 * @return char* Font weight, ou NULL se estilo for inválido.
 */
char* getFWEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna o font size.
 *
 * @param estilo Objeto EstiloTexto.
 * @return int Font size, ou 0 se estilo for inválido.
 */
int getFSEstiloTexto(ESTILOTEXTO estilo);

#endif
