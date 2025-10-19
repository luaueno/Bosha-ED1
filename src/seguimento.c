#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "segmento.h"

typedef struct {
    int id;
    float xi;
    float yi;
    float xf;
    float yf;
    char* cor;
} segmento;

SEGMENTO criaSegmento(int id, float xi, float yi, float xf, float yf, char* cor) {
    segmento *s = (segmento*) malloc(sizeof(segmento));

    if (s == NULL) {
        printf("Falha ao alocar memória para o segmento\n");
        exit(1);
    }

    s->id = id;
    s->xi = xi;
    s->yi = yi;
    s->xf = xf;
    s->yf = yf;

    s->cor = (char*) malloc(strlen(cor) + 1);
    if (s->cor == NULL) {
        printf("Falha ao alocar memória para a cor do segmento\n");
        free(s);
        exit(1);
    }

    strcpy(s->cor, cor);
    return s;
}

int getIDSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    return seg->id;
}

float getXiSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    return seg->xi;
}

float getYiSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    return seg->yi;
}

float getXfSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    return seg->xf;
}

float getYfSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    return seg->yf;
}

char* getCorSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    return seg->cor;
}

void setIDSegmento(SEGMENTO s, int id) {
    segmento *seg = (segmento*) s;
    seg->id = id;
}

void setXiSegmento(SEGMENTO s, float xi) {
    segmento *seg = (segmento*) s;
    seg->xi = xi;
}

void setYiSegmento(SEGMENTO s, float yi) {
    segmento *seg = (segmento*) s;
    seg->yi = yi;
}

void setXfSegmento(SEGMENTO s, float xf) {
    segmento *seg = (segmento*) s;
    seg->xf = xf;
}

void setYfSegmento(SEGMENTO s, float yf) {
    segmento *seg = (segmento*) s;
    seg->yf = yf;
}

void setCorSegmento(SEGMENTO s, char* cor) {
    segmento *seg = (segmento*) s;

    free(seg->cor);
    seg->cor = (char*) malloc(strlen(cor) + 1);

    if (seg->cor == NULL) {
        printf("Falha ao alocar memória para a nova cor\n");
        exit(1);
    }

    strcpy(seg->cor, cor);
}

float calculaMetricaSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    float dx = seg->xf - seg->xi;
    float dy = seg->yf - seg->yi;

    float metrica = 2 * sqrt(pow(dx, 2) + pow(dy, 2));
    return metrica;
}

void liberaSegmento(SEGMENTO s) {
    segmento *seg = (segmento*) s;
    free(seg->cor);
    free(seg);
}
