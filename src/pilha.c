#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NoPilha {
    void *conteudo;
    struct NoPilha *baixo;
} NoPilha;

typedef struct stPilha {
    NoPilha *topo;
    int tamanho;
} stPilha;

/**
 * @brief Cria uma pilha vazia.
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
 * @brief Adiciona um elemento no topo da pilha.
 */
bool pushPilha(Pilha pilha, void *conteudo) {
    if (!pilha) return false;

    stPilha *p = (stPilha *) pilha;
    NoPilha *novo = (NoPilha *) malloc(sizeof(NoPilha));
    if (!novo) {
        printf("[ERRO] Falha ao alocar memória para novo nó da pilha.\n");
        return false;
    }

    novo->conteudo = conteudo;
    novo->baixo = p->topo;
    p->topo = novo;
    p->tamanho++;
    return true;
}

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 */
void* popPilha(Pilha pilha) {
    if (!pilha) return NULL;

    stPilha *p = (stPilha *) pilha;
    if (!p->topo) return NULL;

    NoPilha *remover = p->topo;
    void *conteudo = remover->conteudo;

    p->topo = remover->baixo;
    free(remover);
    p->tamanho--;
    return conteudo;
}

/**
 * @brief Retorna o elemento do topo da pilha sem removê-lo.
 */
void* topoPilha(Pilha pilha) {
    if (!pilha) return NULL;

    stPilha *p = (stPilha *) pilha;
    if (!p->topo) return NULL;

    return p->topo->conteudo;
}

/**
 * @brief Verifica se a pilha está vazia.
 */
bool pilhaVazia(Pilha pilha) {
    if (!pilha) return true;

    stPilha *p = (stPilha *) pilha;
    return (p->tamanho == 0);
}

/**
 * @brief Retorna a quantidade de elementos na pilha.
 */
int tamanhoPilha(Pilha pilha) {
    if (!pilha) return 0;

    stPilha *p = (stPilha *) pilha;
    return p->tamanho;
}

/**
 * @brief Libera toda a memória da pilha.
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
