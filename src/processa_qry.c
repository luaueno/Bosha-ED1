#include "processa_qry.h"
#include "fila.h"
#include "pilha.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "trata_geo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// -------------------- TIPOS -------------------- //
typedef enum { CIRCLE, RECTANGLE, LINE, TEXT } TipoForma;

typedef struct {
    TipoForma tipo;
    void *data;
} Forma_t;

typedef struct {
    int id;
    Pilha *formas;
} Carregador_t;

typedef struct {
    int id;
    double x, y;
    Forma_t *posicao_disparo;
    Carregador_t *carregadorEsquerdo;
    Carregador_t *carregadorDireito;
} Disparador_t;

typedef struct {
    Pilha arena;
    Pilha pilha_para_free;
} Qry_t;

typedef struct {
    double minX, minY, maxX, maxY;
} BoundingBox;

// -------------------- AUXILIARES -------------------- //
static Forma_t *clona_forma(Forma_t *f, double dx, double dy) {
    if(!f) return NULL;
    Forma_t *c = malloc(sizeof(Forma_t));
    c->tipo = f->tipo;
    switch(f->tipo){
        case CIRCLE: {
            Circulo *orig = (Circulo*)f->data;
            Circulo *novo = malloc(sizeof(Circulo));
            *novo = *orig;
            novo->cx += dx; novo->cy += dy;
            c->data = novo;
            break;
        }
        case RECTANGLE: {
            Retangulo *orig = (Retangulo*)f->data;
            Retangulo *novo = malloc(sizeof(Retangulo));
            *novo = *orig;
            novo->x += dx; novo->y += dy;
            c->data = novo;
            break;
        }
        case LINE: {
            Linha *orig = (Linha*)f->data;
            Linha *novo = malloc(sizeof(Linha));
            *novo = *orig;
            novo->x1+=dx; novo->y1+=dy; novo->x2+=dx; novo->y2+=dy;
            c->data = novo;
            break;
        }
        case TEXT: {
            Texto *orig = (Texto*)f->data;
            Texto *novo = malloc(sizeof(Texto));
            *novo = *orig;
            novo->x+=dx; novo->y+=dy;
            c->data = novo;
            break;
        }
    }
    return c;
}

static void desaloca_forma(Forma_t *f){
    if(!f) return;
    if(f->data) free(f->data);
    free(f);
}

static BoundingBox calcula_bounding_box(Forma_t *f){
    BoundingBox bb;
    switch(f->tipo){
        case CIRCLE:{
            Circulo *c=(Circulo*)f->data;
            bb.minX = c->cx - c->r; bb.maxX = c->cx + c->r;
            bb.minY = c->cy - c->r; bb.maxY = c->cy + c->r;
            break;
        }
        case RECTANGLE:{
            Retangulo *r=(Retangulo*)f->data;
            bb.minX = r->x; bb.maxX = r->x + r->w;
            bb.minY = r->y; bb.maxY = r->y + r->h;
            break;
        }
        case LINE:{
            Linha *l=(Linha*)f->data;
            bb.minX = fmin(l->x1,l->x2); bb.maxX = fmax(l->x1,l->x2);
            bb.minY = fmin(l->y1,l->y2); bb.maxY = fmax(l->y1,l->y2);
            break;
        }
        case TEXT:{
            Texto *t=(Texto*)f->data;
            bb.minX = t->x; bb.maxX = t->x + strlen(t->conteudo)*5; // aproximação
            bb.minY = t->y; bb.maxY = t->y + 10;
            break;
        }
    }
    return bb;
}

static bool sobrepoe(BoundingBox a, BoundingBox b){
    return !(a.maxX < b.minX || a.minX > b.maxX || a.maxY < b.minY || a.minY > b.maxY);
}

// -------------------- COMANDOS -------------------- //
static void comando_pd(Disparador_t ***disp, int *cont){
    *disp = realloc(*disp, (*cont+1)*sizeof(Disparador_t*));
    Disparador_t *d = malloc(sizeof(Disparador_t));
    d->id = *cont+1; d->x=0; d->y=0;
    d->posicao_disparo = NULL;
    d->carregadorDireito=NULL; d->carregadorEsquerdo=NULL;
    (*disp)[*cont] = d;
    (*cont)++;
}

static void comando_lc(Carregador_t ***car, int *cont){
    *car = realloc(*car, (*cont+1)*sizeof(Carregador_t*));
    Carregador_t *c = malloc(sizeof(Carregador_t));
    c->id = *cont+1;
    c->formas = criaPilha();
    (*car)[*cont]=c;
    (*cont)++;
}

static void comando_atch(Carregador_t **car, int cont_car, Disparador_t **disp, int cont_disp){
    if(cont_car==0 || cont_disp==0) return;
    Disparador_t *d = disp[cont_disp-1];
    Carregador_t *c = car[cont_car-1];
    d->carregadorDireito = c;
}

static void comando_shft(Disparador_t **disp, int cont){
    if(cont==0) return;
    Disparador_t *d = disp[cont-1];
    d->x+=10; d->y+=10;
}

static void comando_dsp(Disparador_t **disp, int cont, Pilha arena){
    if(cont==0) return;
    Disparador_t *d = disp[cont-1];
    if(!pilhaVazia(*(d->carregadorDireito->formas))){
        Forma_t *f = (Forma_t*)popPilha(*(d->carregadorDireito->formas));
        Forma_t *copia = clona_forma(f,d->x,d->y);
        pushPilha(arena,copia);
    }
}

static void comando_rjd(Disparador_t **disp, int cont, Pilha arena){
    if(cont==0) return;
    Disparador_t *d = disp[cont-1];
    if(!pilhaVazia(arena) && d->carregadorDireito){
        Forma_t *f = (Forma_t*)popPilha(arena);
        pushPilha(*(d->carregadorDireito->formas), f);
    }
}

static void comando_calc(Pilha arena, FILE *txt){
    Pilha aux = criaPilha();
    double soma=0;
    while(!pilhaVazia(arena)){
        Forma_t *f=(Forma_t*)popPilha(arena);
        switch(f->tipo){
            case CIRCLE: { Circulo *c=(Circulo*)f->data; soma+=M_PI*c->r*c->r; break;}
            case RECTANGLE: { Retangulo *r=(Retangulo*)f->data; soma+=r->w*r->h; break;}
            default: break;
        }
        pushPilha(aux,f);
    }
    while(!pilhaVazia(aux)) pushPilha(arena,popPilha(aux));
    desalocaPilha(aux);
    fprintf(txt,"Área total = %.2lf\n",soma);
}

// -------------------- PRINCIPAL -------------------- //
Qry executa_qry(DadosDoArquivo dadosQry, DadosDoArquivo dadosGeo, Chao chao, const char *caminho_output){
    Qry_t *qry = malloc(sizeof(Qry_t));
    qry->arena = criaPilha();
    qry->pilha_para_free = criaPilha();

    Disparador_t **disp = NULL; int cont_disp=0;
    Carregador_t **car = NULL; int cont_car=0;

    FILE *txt = fopen("saida.txt","w");
    while(!filaVazia(obter_fila_linhas(dadosQry))){
        char *linha = (char*)dequeueFila(obter_fila_linhas(dadosQry));
        char *cmd = strtok(linha," \r\n\t");
        if(!cmd) continue;
        if(strcmp(cmd,"pd")==0) comando_pd(&disp,&cont_disp);
        else if(strcmp(cmd,"lc")==0) comando_lc(&car,&cont_car);
        else if(strcmp(cmd,"atch")==0) comando_atch(car,cont_car,disp,cont_disp);
        else if(strcmp(cmd,"shft")==0) comando_shft(disp,cont_disp);
        else if(strcmp(cmd,"dsp")==0) comando_dsp(disp,cont_disp,qry->arena);
        else if(strcmp(cmd,"rjd")==0) comando_rjd(disp,cont_disp,qry->arena);
        else if(strcmp(cmd,"calc")==0) comando_calc(qry->arena,txt);
    }
    fclose(txt);
    cria_svg_com_resultado(dadosQry,dadosGeo,chao,qry->arena,caminho_output);
    return (Qry)qry;
}

void desaloca_qry(Qry qry){
    Qry_t *q = (Qry_t*)qry;
    desalocaPilha(q->arena);
    desalocaPilha(q->pilha_para_free);
    free(q);
}
