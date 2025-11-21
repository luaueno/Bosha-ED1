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
 *
 * IMPORTANTE: agora corretamente definido como ponteiro para struct FilaImpl,
 * que é a estrutura usada no arquivo .c.
 */
typedef struct FilaImpl* Fila;

// =========================================================
// FUNÇÃO CONSTRUTORA
// =========================================================

Fila novaFila();

// =========================================================
// OPERAÇÕES BÁSICAS
// =========================================================

bool enfileirar(Fila f, void *dados);
void* desenfileirar(Fila f);
void* frenteFila(Fila f);
bool filaEstaVazia(Fila f);
int tamanhoFila(Fila f);

// =========================================================
// DESALOCADOR
// =========================================================

void liberarFila(Fila f);

#endif
