#ifndef ESTILO_TEXTO_H
#define ESTILO_TEXTO_H

/**
 * @file estiloTexto.h
 * @brief Módulo para gerenciamento de estilos de texto (EstiloTexto).
 *
 * Este módulo define uma interface para criação, acesso e destruição de objetos que armazenam
 * informações sobre estilo de texto: família da fonte (font family), espessura da fonte
 * (font weight) e tamanho da fonte (font size).
 *
 * A estrutura interna é opaca, garantindo encapsulamento e evitando acesso direto aos campos.
 * A manipulação é feita apenas por meio das funções fornecidas neste header.
 */

#include <stdlib.h>

/**
 * @brief Tipo opaco que representa um estilo de texto.
 */
typedef void* ESTILOTEXTO;

/**
 * @brief Cria um novo objeto EstiloTexto.
 * 
 * @param ff Ponteiro para string com o nome da família da fonte (font family). Não pode ser NULL.
 * @param fw Ponteiro para string com o peso da fonte (font weight), ex: "bold", "normal".
 * @param fs Inteiro representando o tamanho da fonte (font size).
 * 
 * @return ESTILOTEXTO Ponteiro opaco para o objeto criado, ou NULL em caso de falha na alocação
 *         ou se ff for NULL.
 */
ESTILOTEXTO criaEstiloTexto(char* ff, char* fw, int fs);

/**
 * @brief Libera toda a memória associada a um objeto EstiloTexto.
 * 
 * @param estilo Ponteiro retornado por criaEstiloTexto. Se for NULL, nada acontece.
 */
void desalocaEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna a font family de um objeto EstiloTexto.
 * 
 * @param estilo Ponteiro para o objeto EstiloTexto.
 * 
 * @return char* Ponteiro para a string contendo a font family, ou NULL se estilo for NULL.
 */
char* getFFEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna a font weight de um objeto EstiloTexto.
 * 
 * @param estilo Ponteiro para o objeto EstiloTexto.
 * 
 * @return char* Ponteiro para a string contendo a font weight, ou NULL se estilo for NULL.
 */
char* getFWEstiloTexto(ESTILOTEXTO estilo);

/**
 * @brief Retorna o font size de um objeto EstiloTexto.
 * 
 * @param estilo Ponteiro para o objeto EstiloTexto.
 * 
 * @return int Valor inteiro do tamanho da fonte, ou 0 se estilo for NULL.
 */
int getFSEstiloTexto(ESTILOTEXTO estilo);

#endif
