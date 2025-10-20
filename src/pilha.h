/**
 * @file pilha.h
 * @brief Interface do módulo de pilha genérica (estrutura LIFO).
 *
 * Este módulo define uma estrutura de dados do tipo pilha capaz de armazenar
 * qualquer tipo de informação, utilizando ponteiros genéricos (`void*`).
 * A pilha segue o princípio LIFO (Last In, First Out): o último elemento inserido
 * é o primeiro a ser removido.
 *
 * O conteúdo armazenado **não é desalocado automaticamente**, ficando sob
 * responsabilidade do usuário liberar a memória, se necessário.
 */

#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>  /**< Inclui o tipo booleano padrão do C (`true` / `false`). */

/**
 * @brief Tipo opaco que representa uma pilha.
 *
 * A implementação interna é escondida do usuário, que deve manipulá-la
 * apenas por meio das funções fornecidas neste módulo.
 */
typedef void* Pilha;

/* -----------------------------------------------------
   FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO
------------------------------------------------------ */

/**
 * @brief Cria uma nova pilha vazia.
 *
 * @return Ponteiro genérico (`Pilha`) para a pilha criada,
 *         ou NULL em caso de falha de alocação.
 */
Pilha criaPilha();

/**
 * @brief Desaloca toda a memória associada à pilha.
 *
 * @param pilha Ponteiro para a pilha a ser desalocada.
 *
 * @note Esta função libera apenas os nós da pilha.
 *       Os conteúdos armazenados **não** são liberados automaticamente.
 */
void desalocaPilha(Pilha pilha);


/* -----------------------------------------------------
   FUNÇÕES DE OPERAÇÃO (INSERÇÃO E REMOÇÃO)
------------------------------------------------------ */

/**
 * @brief Insere um novo elemento no topo da pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @param conteudo Ponteiro genérico para o conteúdo a ser empilhado.
 *
 * @return true se a operação for bem-sucedida, false caso contrário.
 */
bool pushPilha(Pilha pilha, void *conteudo);

/**
 * @brief Remove o elemento do topo da pilha e o retorna.
 *
 * @param pilha Ponteiro para a pilha.
 *
 * @return Ponteiro para o conteúdo removido,
 *         ou NULL se a pilha estiver vazia ou inválida.
 *
 * @warning O conteúdo apontado não é desalocado automaticamente.
 */
void* popPilha(Pilha pilha);


/* -----------------------------------------------------
   FUNÇÕES DE ACESSO E CONSULTA
------------------------------------------------------ */

/**
 * @brief Retorna o conteúdo do topo da pilha sem removê-lo.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Ponteiro para o conteúdo do topo,
 *         ou NULL se a pilha estiver vazia.
 */
void* topoPilha(Pilha pilha);

/**
 * @brief Verifica se a pilha está vazia.
 *
 * @param pilha Ponteiro para a pilha.
 * @return true se estiver vazia, false caso contrário.
 */
bool pilhaVazia(Pilha pilha);

/**
 * @brief Retorna o número de elementos presentes na pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Inteiro representando o tamanho atual da pilha.
 */
int tamanhoPilha(Pilha pilha);

#endif
