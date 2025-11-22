#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * @file estilo_texto.h
 * @brief Interface para gerenciamento de estilos de texto.
 *
 * Define funções para criação, acesso e destruição
 * de objetos de estilo de texto.
 */

#include <stdlib.h>

/**
 * @brief Tipo opaco que representa um estilo de texto.
 */
typedef void* EstiloTexto;

/**
 * @brief Cria um novo objeto EstiloTexto.
 *
 * @param ff Font family.
 * @param fw Font weight ("normal", "bold", etc).
 * @param fs Font size.
 *
 * @return EstiloTexto Ponteiro opaco para o objeto criado, ou NULL em caso de erro.
 */
EstiloTexto criaEstiloTexto(const char* ff, const char* fw, int fs);

/**
 * @brief Libera toda a memória associada a um EstiloTexto.
 *
 * @param estilo Objeto criado por criaEstiloTexto.
 */
void desalocaEstiloTexto(EstiloTexto estilo);

/**
 * @brief Retorna a font family.
 *
 * @param estilo Objeto EstiloTexto.
 * @return const char* Font family, ou NULL se estilo for inválido.
 */
const char* getFFEstiloTexto(EstiloTexto estilo);

/**
 * @brief Retorna a font weight.
 *
 * @param estilo Objeto EstiloTexto.
 * @return const char* Font weight, ou NULL se estilo for inválido.
 */
const char* getFWEstiloTexto(EstiloTexto estilo);

/**
 * @brief Retorna o font size.
 *
 * @param estilo Objeto EstiloTexto.
 * @return int Font size, ou 0 se estilo for inválido.
 */
int getFSEstiloTexto(EstiloTexto estilo);

#endif
