#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include "estilo_texto.h"

typedef struct {
    int id;
    float x, y;
    char *corB;
    char *corP;
    char ancora;
    char *txt;
    ESTILOTEXTO estilo;   // novo: suporte a estilo de texto
} TextoInterno;

/* ============================================================
 *                       CRIA TEXTO
 * ============================================================ */
TEXTO criaTexto(int id, float x, float y, char *corB, char *corP,
                char ancora, char *txt, ESTILOTEXTO estilo)
{
    TextoInterno *t = malloc(sizeof(TextoInterno));
    if (!t) {
        printf("Erro de alocação em Texto.\n");
        exit(1);
    }

    t->id = id;
    t->x = x;
    t->y = y;
    t->ancora = ancora;
    t->estilo = estilo;

    /* Aloca strings */
    t->corB = malloc(strlen(corB) + 1);
    t->corP = malloc(strlen(corP) + 1);
    t->txt  = malloc(strlen(txt) + 1);

    if (!t->corB || !t->corP || !t->txt) {
        printf("Erro de alocação em Texto.\n");
        exit(1);
    }

    strcpy(t->corB, corB);
    strcpy(t->corP, corP);
    strcpy(t->txt, txt);

    return t;
}

/* ============================================================
 *                          GETTERS
 * ============================================================ */
int getIDTexto(TEXTO t)          { return ((TextoInterno*)t)->id; }
float getXTexto(TEXTO t)         { return ((TextoInterno*)t)->x; }
float getYTexto(TEXTO t)         { return ((TextoInterno*)t)->y; }
char getAncoraTexto(TEXTO t)     { return ((TextoInterno*)t)->ancora; }
char* getCorBTexto(TEXTO t)      { return ((TextoInterno*)t)->corB; }
char* getCorPTexto(TEXTO t)      { return ((TextoInterno*)t)->corP; }
char* getTxtTexto(TEXTO t)       { return ((TextoInterno*)t)->txt; }
ESTILOTEXTO getEstiloTexto(TEXTO t){ return ((TextoInterno*)t)->estilo; }

/* ============================================================
 *                   COMPRIMENTO / LIMITES
 * ============================================================ */
float getComprimentoTexto(TEXTO t)
{
    TextoInterno *ti = t;
    return strlen(ti->txt) * 10.0f;
}

float getX1Texto(TEXTO t)
{
    TextoInterno *ti = t;
    float w = getComprimentoTexto(t);

    switch (ti->ancora) {
        case 'i': case 'I': return ti->x;
        case 'f': case 'F': return ti->x - w;
        case 'm': case 'M': return ti->x - w/2;
        default: return ti->x;
    }
}

float getX2Texto(TEXTO t)
{
    TextoInterno *ti = t;
    float w = getComprimentoTexto(t);

    switch (ti->ancora) {
        case 'i': case 'I': return ti->x + w;
        case 'f': case 'F': return ti->x;
        case 'm': case 'M': return ti->x + w/2;
        default: return ti->x + w;
    }
}

/* ============================================================
 *                          SETTERS
 * ============================================================ */
void setIDTexto(TEXTO t, int id)    { ((TextoInterno*)t)->id = id; }
void setXTexto(TEXTO t, float x)    { ((TextoInterno*)t)->x = x; }
void setYTexto(TEXTO t, float y)    { ((TextoInterno*)t)->y = y; }
void setAncoraTexto(TEXTO t, char a){ ((TextoInterno*)t)->ancora = a; }

void setCorBTexto(TEXTO t, char *cor)
{
    TextoInterno *ti = t;
    free(ti->corB);
    ti->corB = malloc(strlen(cor)+1);
    strcpy(ti->corB, cor);
}

void setCorPTexto(TEXTO t, char *cor)
{
    TextoInterno *ti = t;
    free(ti->corP);
    ti->corP = malloc(strlen(cor)+1);
    strcpy(ti->corP, cor);
}

void setTxtTexto(TEXTO t, char *s)
{
    TextoInterno *ti = t;
    free(ti->txt);
    ti->txt = malloc(strlen(s)+1);
    strcpy(ti->txt, s);
}

/* ============================================================
 *                      DESALOCAÇÃO
 * ============================================================ */
void desalocaTexto(TEXTO t)
{
    TextoInterno *ti = t;
    free(ti->txt);
    free(ti->corB);
    free(ti->corP);
    free(ti);
}
