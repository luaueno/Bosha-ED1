#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

typedef struct {
    int id;
    float x;
    float y;
    float largura;
    float altura;
    char *corP;
    char *corB;
} RetanguloInterno;

RETANGULO novoRetangulo(int id, float x, float y, float largura, float altura, char* corP, char* corB) {
    RetanguloInterno* r = malloc(sizeof(RetanguloInterno));
    if(!r){ printf("Erro de alocação.\n"); exit(1); }

    r->id = id; r->x = x; r->y = y; r->largura = largura; r->altura = altura;

    r->corB = malloc(strlen(corB)+1); r->corP = malloc(strlen(corP)+1);
    if(!r->corB || !r->corP){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(r->corB, corB); strcpy(r->corP, corP);

    return r;
}

int obterIDRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->id; }
float obterXRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->x; }
float obterYRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->y; }
float obterLarguraRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->largura; }
float obterAlturaRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->altura; }
char* obterCorBRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->corB; }
char* obterCorPRetangulo(RETANGULO r){ return ((RetanguloInterno*)r)->corP; }

void definirIDRetangulo(RETANGULO r, int id){ ((RetanguloInterno*)r)->id = id; }
void definirXRetangulo(RETANGULO r, float x){ ((RetanguloInterno*)r)->x = x; }
void definirYRetangulo(RETANGULO r, float y){ ((RetanguloInterno*)r)->y = y; }
void definirLarguraRetangulo(RETANGULO r, float largura){ ((RetanguloInterno*)r)->largura = largura; }
void definirAlturaRetangulo(RETANGULO r, float altura){ ((RetanguloInterno*)r)->altura = altura; }

void definirCorBRetangulo(RETANGULO r, char* corB){
    RetanguloInterno* ri = r;
    free(ri->corB); ri->corB = malloc(strlen(corB)+1);
    if(!ri->corB){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ri->corB, corB);
}

void definirCorPRetangulo(RETANGULO r, char* corP){
    RetanguloInterno* ri = r;
    free(ri->corP); ri->corP = malloc(strlen(corP)+1);
    if(!ri->corP){ printf("Erro de alocação.\n"); exit(1); }
    strcpy(ri->corP, corP);
}

float calcularAreaRetangulo(RETANGULO r){
    RetanguloInterno* ri = r;
    return ri->largura * ri->altura;
}

void liberarRetangulo(RETANGULO r){
    RetanguloInterno* ri = r;
    free(ri->corB); free(ri->corP); free(ri);
}
