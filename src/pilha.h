#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @file pilha.h
 * @brief Módulo de implementação de uma pilha genérica em C.
 *
 * Este módulo fornece funções para manipular uma estrutura de dados do tipo pilha (stack)
 * com alocação dinâmica. A pilha segue a política LIFO (Last In, First Out).
 * Os elementos armazenados são ponteiros genéricos (`void*`), permitindo flexibilidade.
 *
 * O gerenciamento da memória dos dados armazenados é responsabilidade do usuário.
 */

/**
 * @brief Tipo opaco que representa uma pilha genérica.
 * O ponteiro é tratado internamente como `struct stPilha*`.
 */
typedef void* Pilha;

/**
 * @brief Cria uma nova pilha vazia.
 * @return Ponteiro opaco para a pilha criada ou NULL em caso de falha.
 */
Pilha criaPilha();

/**
 * @brief Adiciona um elemento no topo da pilha.
 * @param pilha Pilha onde o elemento será adicionado.
 * @param conteudo Ponteiro para o conteúdo a ser armazenado.
 * @return true se a operação for bem-sucedida, false caso contrário.
 */
bool pushPilha(Pilha pilha, void *conteudo);

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 * @param pilha Pilha de onde o elemento será removido.
 * @return Ponteiro para o conteúdo removido ou NULL se a pilha estiver vazia.
 */
void* popPilha(Pilha pilha);

/**
 * @brief Retorna o elemento do topo da pilha sem removê-lo.
 * @param pilha Pilha a ser consultada.
 * @return Ponteiro para o conteúdo do topo ou NULL se a pilha estiver vazia.
 */
void* topoPilha(Pilha pilha);

/**
 * @brief Verifica se a pilha está vazia.
 * @param pilha Pilha a ser verificada.
 * @return true se a pilha estiver vazia, false caso contrário.
 */
bool pilhaVazia(Pilha pilha);

/**
 * @brief Retorna a quantidade de elementos na pilha.
 * @param pilha Pilha a ser consultada.
 * @return Número de elementos na pilha ou 0 se a pilha for NULL.
 */
int tamanhoPilha(Pilha pilha);

/**
 * @brief Libera toda a memória alocada pela pilha.
 * @param pilha Pilha a ser desalocada.
 */
void desalocaPilha(Pilha pilha);

#endif
