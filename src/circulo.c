#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"

// Estrutura que representa um círculo e suas propriedades básicas
typedef struct {
    int id;
    float cx;
    float cy;
    float r;
    char *borda;
    char *preench;
} CirculoImpl;

// Cria um novo círculo na memória e inicializa seus atributos
CIRCULO novoCirculo(int id, float cx, float cy, float r, char *borda, char *preench) {
    CirculoImpl *circ = (CirculoImpl *) malloc(sizeof(CirculoImpl));

    if (circ == NULL) {
        fprintf(stderr, "Falha ao alocar memória para círculo.\n");
        exit(1);
    }

    circ->id = id;
    circ->cx = cx;
    circ->cy = cy;
    circ->r = r;

    circ->borda = (char *) malloc(strlen(borda) + 1);
    circ->preench = (char *) malloc(strlen(preench) + 1);

    if (circ->borda == NULL || circ->preench == NULL) {
        fprintf(stderr, "Erro de alocação de memória para cores.\n");
        free(circ);
        exit(1);
    }

    strcpy(circ->borda, borda);
    strcpy(circ->preench, preench);

    return circ;
}

// ======== Funções GET ========

int getIdCirc(CIRCULO c) {
    return ((CirculoImpl *) c)->id;
}

float getCentroXCirc(CIRCULO c) {
    return ((CirculoImpl *) c)->cx;
}

float getCentroYCirc(CIRCULO c) {
    return ((CirculoImpl *) c)->cy;
}

float getRaioCirc(CIRCULO c) {
    return ((CirculoImpl *) c)->r;
}

char *getCorBordaCirc(CIRCULO c) {
    return ((CirculoImpl *) c)->borda;
}

char *getCorPreenchCirc(CIRCULO c) {
    return ((CirculoImpl *) c)->preench;
}

// ======== Funções SET ========

void setIdCirc(CIRCULO c, int id) {
    ((CirculoImpl *) c)->id = id;
}

void setCentroXCirc(CIRCULO c, float x) {
    ((CirculoImpl *) c)->cx = x;
}

void setCentroYCirc(CIRCULO c, float y) {
    ((CirculoImpl *) c)->cy = y;
}

void setRaioCirc(CIRCULO c, float r) {
    ((CirculoImpl *) c)->r = r;
}

void setCorBordaCirc(CIRCULO c, char *borda) {
    CirculoImpl *circ = (CirculoImpl *) c;
    free(circ->borda);
    circ->borda = (char *) malloc(strlen(borda) + 1);

    if (circ->borda == NULL) {
        fprintf(stderr, "Erro ao alocar memória para cor da borda.\n");
        exit(1);
    }

    strcpy(circ->borda, borda);
}

void setCorPreenchCirc(CIRCULO c, char *preench) {
    CirculoImpl *circ = (CirculoImpl *) c;
    free(circ->preench);
    circ->preench = (char *) malloc(strlen(preench) + 1);

    if (circ->preench == NULL) {
        fprintf(stderr, "Erro ao alocar memória para cor de preenchimento.\n");
        exit(1);
    }

    strcpy(circ->preench, preench);
}

// ======== Funções utilitárias ========

// Calcula a área do círculo com base no raio
float areaCirc(CIRCULO c) {
    CirculoImpl *circ = (CirculoImpl *) c;
    return 3.14f * (circ->r * circ->r);
}

// Libera toda a memória associada ao círculo
void liberarCirc(CIRCULO c) {
    CirculoImpl *circ = (CirculoImpl *) c;
    free(circ->borda);
    free(circ->preench);
    free(circ);
}
