#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"

typedef struct {
    int id;
    float x, y;      // Posição
    char* txt;       // Conteúdo textual
    char* corB;      // Cor da borda
    char* corP;      // Cor de preenchimento
    char ancora;     // 'i' = início, 'f' = fim, 'm' = meio
} TextoInterno;

/* ======== CRIAÇÃO ======== */
TEXTO novoTexto(int id, float x, float y, char* corB, char* corP, char ancora, char* txt){
    TextoInterno* t = malloc(sizeof(TextoInterno));
    if(!t){ printf("Erro de alocação.\n"); exit(1); }

    t->id = id; t->x = x; t->y = y; t->ancora = ancora;

    t->corB = malloc(strlen(corB)+1);
    t->corP = malloc(strlen(corP)+1);
    t->txt  = malloc(strlen(txt)+1);

    if(!t->corB || !t->corP || !t->txt){ printf("Erro de alocação.\n"); exit(1); }

    strcpy(t->corB, corB);
    strcpy(t->corP, corP);
    strcpy(t->txt, txt);

    return t;
}

/* ======== GET ======== */
int obterIDTexto(TEXTO t){ return ((TextoInterno*)t)->id; }
float obterXTexto(TEXTO t){ return ((TextoInterno*)t)->x; }
float obterYTexto(TEXTO t){ return ((TextoInterno*)t)->y; }
char obterAncoraTexto(TEXTO t){ return ((TextoInterno*)t)->ancora; }
char* obterCorBTexto(TEXTO t){ return ((TextoInterno*)t)->corB; }
char* obterCorPTexto(TEXTO t){ return ((TextoInterno*)t)->corP; }
char* obterConteudoTexto(TEXTO t){ return ((TextoInterno*)t)->txt; }

/* ======== COMPRIMENTO E LIMITES ======== */
float obterComprimentoTexto(TEXTO t){
    TextoInterno* ti = t;
    return strlen(ti->txt) * 10.0f; // largura aproximada por caractere
}

float obterX1Texto(TEXTO t){
    TextoInterno* ti = t;
    float cl = obterComprimentoTexto(t);
    switch(ti->ancora){
        case 'i': return ti->x;
        case 'f': return ti->x - cl;
        case 'm': return ti->x - cl/2;
        default: printf("Âncora inválida\n"); return ti->x;
    }
}

float obterX2Texto(TEXTO t){
    TextoInterno* ti = t;
    float cl = obterComprimentoTexto(t);
    switch(ti->ancora){
        case 'i': return ti->x + cl;
        case 'f': return ti->x;
        case 'm': return ti->x + cl/2;
        default: return ti->x + cl;
    }
}

/* ======== SET ======== */
void definirIDTexto(TEXTO t, int id){ ((TextoInterno*)t)->id = id; }
void definirXTexto(TEXTO t, float x){ ((TextoInterno*)t)->x = x; }
void definirYTexto(TEXTO t, float y){ ((TextoInterno*)t)->y = y; }

void definirCorBTexto(TEXTO t, char* corB){
    TextoInterno* ti = t;
    free(ti->corB);
    ti->corB = malloc(strlen(corB)+1);
    if(!ti->corB){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ti->corB, corB);
}

void definirCorPTexto(TEXTO t, char* corP){
    TextoInterno* ti = t;
    free(ti->corP);
    ti->corP = malloc(strlen(corP)+1);
    if(!ti->corP){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ti->corP, corP);
}

void definirAncoraTexto(TEXTO t, char ancora){ ((TextoInterno*)t)->ancora = ancora; }

void definirConteudoTexto(TEXTO t, char* txt){
    TextoInterno* ti = t;
    free(ti->txt);
    ti->txt = malloc(strlen(txt)+1);
    if(!ti->txt){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ti->txt, txt);
}

/* ======== MÉTODOS ADICIONAIS ======== */
float calcularAreaTexto(TEXTO t){
    TextoInterno* ti = t;
    return strlen(ti->txt) * 20.0f; // área aproximada (altura fixa 20)
}

/* ======== DESALOCAÇÃO ======== */
void liberarTexto(TEXTO t){
    TextoInterno* ti = t;
    free(ti->txt);
    free(ti->corB);
    free(ti->corP);
    free(ti);
}
