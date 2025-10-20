#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

// =========================================================
// Estruturas internas da Fila
// =========================================================

// Nó individual da fila (armazenamento genérico)
typedef struct NodoFila {
    void *dados;
    struct NodoFila *proximo;
} NodoFila;

// Estrutura principal da fila (implementação interna)
typedef struct FilaImpl {
    NodoFila *primeiro;
    NodoFila *ultimo;
    int qtd;
} FilaImpl;

// =========================================================
// FUNÇÃO CONSTRUTORA
// =========================================================

Fila novaFila() {
    FilaImpl *fila = (FilaImpl *) malloc(sizeof(FilaImpl));

    if (fila == NULL) {
        fprintf(stderr, "[ERRO] Não foi possível alocar memória para a fila.\n");
        return NULL;
    }

    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->qtd = 0;

    return (Fila) fila;
}

// =========================================================
// OPERAÇÕES BÁSICAS
// =========================================================

/**
 * @brief Insere um novo elemento no final da fila.
 * @param f Ponteiro para a fila.
 * @param dados Ponteiro genérico para o conteúdo a ser inserido.
 * @return true se a operação for bem-sucedida, false caso contrário.
 */
bool enfileirar(Fila f, void *dados) {
    if (f == NULL) return false;

    FilaImpl *fila = (FilaImpl *) f;
    NodoFila *novo = (NodoFila *) malloc(sizeof(NodoFila));

    if (novo == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memória para o nó da fila.\n");
        return false;
    }

    novo->dados = dados;
    novo->proximo = NULL;

    if (fila->ultimo != NULL)
        fila->ultimo->proximo = novo;
    else
        fila->primeiro = novo;

    fila->ultimo = novo;
    fila->qtd++;

    return true;
}

/**
 * @brief Remove e retorna o primeiro elemento da fila.
 * @param f Ponteiro para a fila.
 * @return void* Conteúdo removido, ou NULL se a fila estiver vazia.
 */
void* desenfileirar(Fila f) {
    if (f == NULL) return NULL;

    FilaImpl *fila = (FilaImpl *) f;
    if (fila->primeiro == NULL) return NULL;

    NodoFila *removido = fila->primeiro;
    void *dados = removido->dados;

    fila->primeiro = removido->proximo;
    if (fila->primeiro == NULL)
        fila->ultimo = NULL;

    free(removido);
    fila->qtd--;

    return dados;
}

/**
 * @brief Retorna o primeiro elemento da fila sem removê-lo.
 * @param f Ponteiro para a fila.
 * @return void* Conteúdo do primeiro nó, ou NULL se vazia.
 */
void* frenteFila(Fila f) {
    if (f == NULL) return NULL;

    FilaImpl *fila = (FilaImpl *) f;
    if (fila->primeiro == NULL) return NULL;

    return fila->primeiro->dados;
}

/**
 * @brief Verifica se a fila está vazia.
 * @param f Ponteiro para a fila.
 * @return true se vazia, false caso contrário.
 */
bool filaEstaVazia(Fila f) {
    if (f == NULL) return true;

    FilaImpl *fila = (FilaImpl *) f;
    return (fila->qtd == 0);
}

/**
 * @brief Retorna o número de elementos na fila.
 * @param f Ponteiro para a fila.
 * @return int Quantidade de elementos.
 */
int tamanhoFila(Fila f) {
    if (f == NULL) return 0;

    FilaImpl *fila = (FilaImpl *) f;
    return fila->qtd;
}

// =========================================================
// DESALOCADOR
// =========================================================

/**
 * @brief Libera toda a memória associada à fila.
 * @param f Ponteiro para a fila a ser destruída.
 */
void liberarFila(Fila f) {
    if (f == NULL) return;

    FilaImpl *fila = (FilaImpl *) f;
    NodoFila *atual = fila->primeiro;

    while (atual != NULL) {
        NodoFila *prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    free(fila);
}
