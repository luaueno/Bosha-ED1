/**
 * @file pilha.c
 * @brief Implementação de uma pilha genérica (estrutura LIFO).
 *
 * Este módulo implementa uma pilha capaz de armazenar qualquer tipo de dado
 * por meio de ponteiros genéricos (`void*`). A pilha segue o princípio LIFO
 * (Last In, First Out), ou seja, o último elemento inserido é o primeiro a ser removido.
 *
 * Cada nó contém um ponteiro para o conteúdo armazenado e uma referência
 * para o nó logo abaixo na pilha.
 */

#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------
   Estruturas internas da pilha
--------------------------------*/

/**
 * @brief Estrutura interna que representa um nó da pilha.
 * Cada nó armazena um ponteiro genérico para o conteúdo e
 * um ponteiro para o próximo nó abaixo.
 */
typedef struct NoPilha {
    void *conteudo;           /**< Ponteiro genérico para o conteúdo armazenado. */
    struct NoPilha *baixo;    /**< Ponteiro para o próximo nó abaixo na pilha. */
} NoPilha;

/**
 * @brief Estrutura principal da pilha.
 * Contém o ponteiro para o topo e o contador de elementos.
 */
typedef struct stPilha {
    NoPilha *topo;            /**< Ponteiro para o nó no topo da pilha. */
    int tamanho;              /**< Quantidade de elementos atualmente na pilha. */
} stPilha;


/* -------------------------------
   Funções públicas da pilha
--------------------------------*/

/**
 * @brief Cria e inicializa uma pilha vazia.
 *
 * @return Ponteiro genérico (Pilha) para a estrutura criada,
 *         ou NULL em caso de falha na alocação.
 */
Pilha criaPilha() {

    stPilha *pilha = (stPilha *) malloc(sizeof(stPilha));
    if (!pilha) {
        printf("[ERRO] Falha ao alocar memória para a pilha.\n");
        return NULL;
    }

    pilha->topo = NULL;
    pilha->tamanho = 0;

    return (Pilha) pilha;
}


/**
 * @brief Insere um novo elemento no topo da pilha.
 *
 * @param pilha Ponteiro para a pilha onde o elemento será adicionado.
 * @param conteudo Ponteiro genérico para o conteúdo que será empilhado.
 *
 * @return true se o elemento foi adicionado com sucesso, false em caso de erro.
 */
bool pushPilha(Pilha pilha, void *conteudo) {

    if (!pilha) return false;

    stPilha *p = (stPilha *) pilha;

    /* Criação de um novo nó */
    NoPilha *novo = (NoPilha *) malloc(sizeof(NoPilha));
    if (!novo) {
        printf("[ERRO] Falha ao alocar memória para novo nó da pilha.\n");
        return false;
    }

    novo->conteudo = conteudo;
    novo->baixo = p->topo;  /* O antigo topo passa a ser o "baixo" do novo nó */
    p->topo = novo;         /* Atualiza o topo da pilha */
    p->tamanho++;

    return true;
}


/**
 * @brief Remove e retorna o elemento que está no topo da pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Ponteiro para o conteúdo removido, ou NULL se a pilha estiver vazia.
 *
 * @warning O conteúdo apontado não é desalocado automaticamente.
 *          A responsabilidade de liberar a memória é do usuário.
 */
void* popPilha(Pilha pilha) {

    if (!pilha) return NULL;

    stPilha *p = (stPilha *) pilha;
    if (!p->topo) return NULL;

    NoPilha *remover = p->topo;
    void *conteudo = remover->conteudo;

    /* Atualiza o topo e libera o nó */
    p->topo = remover->baixo;
    free(remover);
    p->tamanho--;

    return conteudo;
}


/**
 * @brief Retorna o conteúdo do topo da pilha sem removê-lo.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Ponteiro para o conteúdo do topo, ou NULL se a pilha estiver vazia.
 */
void* topoPilha(Pilha pilha) {

    if (!pilha) return NULL;

    stPilha *p = (stPilha *) pilha;
    if (!p->topo) return NULL;

    return p->topo->conteudo;
}


/**
 * @brief Verifica se a pilha está vazia.
 *
 * @param pilha Ponteiro para a pilha.
 * @return true se estiver vazia, false caso contrário.
 */
bool pilhaVazia(Pilha pilha) {

    if (!pilha) return true;

    stPilha *p = (stPilha *) pilha;
    return (p->tamanho == 0);
}


/**
 * @brief Retorna a quantidade de elementos na pilha.
 *
 * @param pilha Ponteiro para a pilha.
 * @return Número de elementos, ou 0 se a pilha for inválida.
 */
int tamanhoPilha(Pilha pilha) {

    if (!pilha) return 0;

    stPilha *p = (stPilha *) pilha;
    return p->tamanho;
}


/**
 * @brief Libera toda a memória associada à pilha.
 *
 * @param pilha Ponteiro para a pilha a ser desalocada.
 *
 * @note Esta função apenas desaloca a estrutura da pilha e seus nós.
 *       Os conteúdos armazenados não são liberados automaticamente.
 */
void desalocaPilha(Pilha pilha) {

    if (!pilha) return;

    stPilha *p = (stPilha *) pilha;

    NoPilha *atual = p->topo;
    while (atual) {
        NoPilha *anterior = atual->baixo;
        free(atual);
        atual = anterior;
    }

    free(p);
}
