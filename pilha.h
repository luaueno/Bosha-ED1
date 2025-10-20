#ifndef PILHA_H
#define PILHA_H

/**
 * @file pilha.h
 * @brief Interface para o módulo de Pilha genérica em C.
 *
 * Este módulo fornece uma implementação de pilha (stack) utilizando
 * lista encadeada simples, permitindo inserção e remoção apenas no topo
 * da pilha (política LIFO — Last In, First Out).
 *
 * O tipo opaco `Pilha` garante que a implementação interna seja escondida
 * do usuário, permitindo apenas acesso via funções da interface.
 *
 * O gerenciamento da memória dos dados armazenados (conteúdo dos ponteiros)
 * é responsabilidade do usuário.
 */

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Tipo opaco que representa uma pilha genérica.
 */
typedef void* Pilha;

/**
 * @brief Cria uma pilha vazia.
 * 
 * @return Ponteiro opaco para a nova pilha ou NULL em caso de erro.
 */
Pilha criaPilha();

/**
 * @brief Adiciona um elemento no topo da pilha.
 * 
 * @param pilha Ponteiro para a pilha
 * @param dado Ponteiro para o conteúdo a ser armazenado
 * @return true se a operação foi bem-sucedida, false caso contrário
 */
bool pushPilha(Pilha pilha, void *dado);

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 * 
 * @param pilha Ponteiro para a pilha
 * @return Ponteiro para o conteúdo removido ou NULL se a pilha estiver vazia
 */
void* popPilha(Pilha pilha);

/**
 * @brief Retorna o elemento do topo da pilha sem removê-lo.
 * 
 * @param pilha Ponteiro para a pilha
 * @return Ponteiro para o conteúdo do topo ou NULL se a pilha estiver vazia
 */
void* topoPilha(Pilha pilha);

/**
 * @brief Verifica se a pilha está vazia.
 * 
 * @param pilha Ponteiro para a pilha
 * @return true se a pilha estiver vazia, false caso contrário
 */
bool pilhaVazia(Pilha pilha);

/**
 * @brief Retorna a quantidade de elementos na pilha.
 * 
 * @param pilha Ponteiro para a pilha
 * @return Número de elementos
 */
int tamanhoPilha(Pilha pilha);

/**
 * @brief Desaloca toda a memória associada à pilha.
 * 
 * @param pilha Ponteiro para a pilha a ser desalocada
 */
void desalocaPilha(Pilha pilha);

#endif
