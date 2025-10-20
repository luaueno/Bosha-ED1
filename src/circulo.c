#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"

typedef struct {
    int id;
    float x;
    float y;
    float raio;
    char *corP;
    char *corB;
} CirculoInterno;

CIRCULO novoCirculo(int id, float x, float y, float raio, char* corP, char* corB) {
    CirculoInterno* c = malloc(sizeof(CirculoInterno));
    if(!c){ printf("Erro de alocação.\n"); exit(1); }

    c->id = id; c->x = x; c->y = y; c->raio = raio;

    c->corB = malloc(strlen(corB)+1);
    c->corP = malloc(strlen(corP)+1);
    if(!c->corB || !c->corP){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(c->corB, corB); strcpy(c->corP, corP);

    return c;
}

int obterIDCirculo(CIRCULO c){ return ((CirculoInterno*)c)->id; }
float obterXCirculo(CIRCULO c){ return ((CirculoInterno*)c)->x; }
float obterYCirculo(CIRCULO c){ return ((CirculoInterno*)c)->y; }
float obterRaioCirculo(CIRCULO c){ return ((CirculoInterno*)c)->raio; }
char* obterCorBCirculo(CIRCULO c){ return ((CirculoInterno*)c)->corB; }
char* obterCorPCirculo(CIRCULO c){ return ((CirculoInterno*)c)->corP; }

void definirIDCirculo(CIRCULO c, int id){ ((CirculoInterno*)c)->id = id; }
void definirXCirculo(CIRCULO c, float x){ ((CirculoInterno*)c)->x = x; }
void definirYCirculo(CIRCULO c, float y){ ((CirculoInterno*)c)->y = y; }
void definirRaioCirculo(CIRCULO c, float r){ ((CirculoInterno*)c)->raio = r; }

void definirCorBCirculo(CIRCULO c, char* corB){
    CirculoInterno* ci = c;
    free(ci->corB); ci->corB = malloc(strlen(corB)+1);
    if(!ci->corB){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ci->corB, corB);
}

void definirCorPCirculo(CIRCULO c, char* corP){
    CirculoInterno* ci = c;
    free(ci->corP); ci->corP = malloc(strlen(corP)+1);
    if(!ci->corP){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ci->corP, corP);
}

float calcularAreaCirculo(CIRCULO c){ 
    CirculoInterno* ci = c;
    return 3.14f * ci->raio * ci->raio;
}

void liberarCirculo(CIRCULO c){
    CirculoInterno* ci = c;
    free(ci->corB); free(ci->corP); free(ci);
}
