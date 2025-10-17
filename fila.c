#ifndef FILA_H
#define FILA_H

/**
 * @file fila.h
 * @brief Implementação genérica de fila (FIFO) em C.
 *
 * Estrutura genérica de fila usando ponteiros void* para qualquer tipo de dado.
 * Suporta inserção no final, remoção do início, consulta ao início e verificação de vazio.
 */

#include <stdbool.h>
#include <stdlib.h>

typedef void* Fila;

/**
 * @brief Cria uma nova fila vazia.
 * @return Ponteiro para a fila criada.
 */
Fila criarFila();

/**
 * @brief Adiciona um elemento no final da fila.
 * @param f Ponteiro para a fila.
 * @param item Conteúdo a ser inserido.
 * @return true se inserido com sucesso, false caso contrário.
 */
bool adicionarFila(Fila f, void *item);

/**
 * @brief Remove o primeiro elemento da fila.
 * @param f Ponteiro para a fila.
 * @return Conteúdo removido ou NULL se estiver vazia.
 */
void* removerFila(Fila f);

/**
 * @brief Retorna o primeiro elemento sem removê-lo.
 * @param f Ponteiro para a fila.
 * @return Conteúdo do início ou NULL se vazia.
 */
void* frenteFila(Fila f);

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro para a fila.
 * @return true se vazia, false caso contrário.
 */
bool estaVazia(Fila f);

/**
 * @brief Retorna a quantidade de elementos da fila.
 * @param f Ponteiro para a fila.
 * @return Número de elementos.
 */
int tamanhoFila(Fila f);

/**
 * @brief Libera toda a memória da fila.
 * @param f Ponteiro para a fila.
 */
void liberarFila(Fila f);

#endif


