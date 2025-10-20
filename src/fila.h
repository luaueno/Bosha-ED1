#ifndef FILA_H
#define FILA_H

/**
 * @file fila.h
 * @brief Interface para a implementação de uma fila genérica em C.
 *
 * Este módulo define uma estrutura abstrata de fila (queue) baseada em lista encadeada,
 * permitindo inserções no final e remoções no início (política FIFO — First In, First Out).
 *
 * Os elementos armazenados são do tipo `void*`, o que torna o módulo genérico.
 * O controle da memória dos conteúdos inseridos é de responsabilidade do usuário.
 *
 * Funcionalidades:
 *  - Criação e liberação de filas
 *  - Inserção e remoção de elementos
 *  - Consulta ao início da fila
 *  - Verificação se está vazia
 *  - Consulta ao tamanho atual
 */

#include <stdbool.h>
#include <stdlib.h>

/**
 * @typedef Fila
 * @brief Tipo opaco que representa uma fila genérica.
 */
typedef void* Fila;

// =========================================================
// FUNÇÃO CONSTRUTORA
// =========================================================

/**
 * @brief Cria e inicializa uma nova fila vazia.
 *
 * @return Fila Ponteiro genérico para a fila criada, ou NULL em caso de erro.
 */
Fila novaFila();

// =========================================================
// OPERAÇÕES BÁSICAS
// =========================================================

/**
 * @brief Insere um novo elemento no final da fila.
 *
 * @param f Ponteiro para a fila.
 * @param dados Ponteiro genérico para o conteúdo a ser armazenado.
 * @return true se a operação for bem-sucedida, false caso contrário.
 */
bool enfileirar(Fila f, void *dados);

/**
 * @brief Remove e retorna o primeiro elemento da fila.
 *
 * @param f Ponteiro para a fila.
 * @return void* Ponteiro para o conteúdo removido, ou NULL se vazia.
 */
void* desenfileirar(Fila f);

/**
 * @brief Retorna o conteúdo do primeiro elemento sem removê-lo.
 *
 * @param f Ponteiro para a fila.
 * @return void* Ponteiro para o conteúdo do início, ou NULL se vazia.
 */
void* frenteFila(Fila f);

/**
 * @brief Verifica se a fila está vazia.
 *
 * @param f Ponteiro para a fila.
 * @return true se estiver vazia, false caso contrário.
 */
bool filaEstaVazia(Fila f);

/**
 * @brief Retorna o número de elementos atualmente armazenados na fila.
 *
 * @param f Ponteiro para a fila.
 * @return int Quantidade de elementos.
 */
int tamanhoFila(Fila f);

// =========================================================
// DESALOCADOR
// =========================================================

/**
 * @brief Libera toda a memória alocada para a fila (mas não o conteúdo dos nós).
 *
 * @param f Ponteiro para a fila a ser liberada.
 */
void liberarFila(Fila f);

#endif
