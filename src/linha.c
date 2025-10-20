#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linha.h"

/**
 * Estrutura interna da linha. Não visível fora deste módulo.
 */
typedef struct {
    int id;       /**< Identificador da linha */
    float x1;     /**< Coordenada X do ponto inicial */
    float y1;     /**< Coordenada Y do ponto inicial */
    float x2;     /**< Coordenada X do ponto final */
    float y2;     /**< Coordenada Y do ponto final */
    char *cor;    /**< Cor da linha */
} LinhaInterna;

/* ======== CRIAÇÃO ======== */
LINHA novaLinha(int id, float x1, float y1, float x2, float y2, char *cor) {
    LinhaInterna *l = malloc(sizeof(LinhaInterna));
    if (!l) { printf("Erro de alocação.\n"); exit(1); }

    l->id = id; l->x1 = x1; l->y1 = y1; l->x2 = x2; l->y2 = y2;
    l->cor = malloc(strlen(cor)+1);
    if (!l->cor) { printf("Erro de alocação.\n"); exit(1); }
    strcpy(l->cor, cor);

    return l;
}

/* ======== MÉTODOS GET ======== */
int obterIDLinha(LINHA l) { return ((LinhaInterna*)l)->id; }
float obterX1Linha(LINHA l) { return ((LinhaInterna*)l)->x1; }
float obterY1Linha(LINHA l) { return ((LinhaInterna*)l)->y1; }
float obterX2Linha(LINHA l) { return ((LinhaInterna*)l)->x2; }
float obterY2Linha(LINHA l) { return ((LinhaInterna*)l)->y2; }
char* obterCorLinha(LINHA l) { return ((LinhaInterna*)l)->cor; }

/* ======== MÉTODOS SET ======== */
void definirIDLinha(LINHA l, int id) { ((LinhaInterna*)l)->id = id; }
void definirX1Linha(LINHA l, float x1) { ((LinhaInterna*)l)->x1 = x1; }
void definirY1Linha(LINHA l, float y1) { ((LinhaInterna*)l)->y1 = y1; }
void definirX2Linha(LINHA l, float x2) { ((LinhaInterna*)l)->x2 = x2; }
void definirY2Linha(LINHA l, float y2) { ((LinhaInterna*)l)->y2 = y2; }

/**
 * Define a cor da linha. Libera a memória antiga antes de copiar a nova string.
 */
void definirCorLinha(LINHA l, char *cor) {
    LinhaInterna *li = l;
    free(li->cor);
    li->cor = malloc(strlen(cor)+1);
    if (!li->cor) { printf("Erro de alocação.\n"); exit(1); }
    strcpy(li->cor, cor);
}

/* ======== MÉTODOS ADICIONAIS ======== */
/**
 * Calcula a "área" da linha como 2 * comprimento da linha (para compatibilidade).
 */
float calcularAreaLinha(LINHA l) {
    LinhaInterna *li = l;
    float dx = li->x1 - li->x2;
    float dy = li->y1 - li->y2;
    return 2 * sqrt(dx*dx + dy*dy);
}

/* ======== DESALOCAÇÃO ======== */
void liberarLinha(LINHA l) {
    LinhaInterna *li = l;
    free(li->cor);
    free(li);
}

