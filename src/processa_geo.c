#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processa_geo.h"
#include "fila.h"
#include "pilha.h"
#include "linha.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "estilo_texto.h"

typedef enum TipoForma {
    CIRCLE,
    RECTANGLE,
    LINE,
    TEXT,
    TEXT_STYLE
} TipoForma;

typedef struct {
    TipoForma tipo;
    void *data;
} Forma_t;

typedef struct {
    Fila fila_formas;
    Fila fila_svg;
    Pilha pilha_para_free;
    ESTILOTEXTO estiloAtual;
} Chao_t;

ProcessaGeo inicia_processa_geo() {
    Chao_t *chao = malloc(sizeof(Chao_t));
    if (!chao) {
        printf("Erro ao alocar chao\n");
        exit(1);
    }

    chao->fila_formas = criaFila();
    chao->fila_svg = criaFila();
    chao->pilha_para_free = criaPilha();
    chao->estiloAtual = NULL;

    return chao;
}

static void executa_comando_circulo(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *cx = strtok(NULL, " ");
    char *cy = strtok(NULL, " ");
    char *r = strtok(NULL, " ");
    char *corb = strtok(NULL, " ");
    char *corp = strtok(NULL, " ");

    CIRCULO c = criaCirculo(id, atof(cx), atof(cy), atof(r), corb, corp);

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = CIRCLE;
    forma->data = c;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

static void executa_comando_retangulo(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *x = strtok(NULL, " ");
    char *y = strtok(NULL, " ");
    char *w = strtok(NULL, " ");
    char *h = strtok(NULL, " ");
    char *corb = strtok(NULL, " ");
    char *corp = strtok(NULL, " ");

    RETANGULO r = criaRetangulo(id, atof(x), atof(y), atof(w), atof(h), corb, corp);

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = RECTANGLE;
    forma->data = r;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

static void executa_comando_linha(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *x1 = strtok(NULL, " ");
    char *y1 = strtok(NULL, " ");
    char *x2 = strtok(NULL, " ");
    char *y2 = strtok(NULL, " ");
    char *cor = strtok(NULL, " ");

    LINHA linha = criaLinha(id, atof(x1), atof(y1), atof(x2), atof(y2), cor);

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = LINE;
    forma->data = linha;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

static void executa_comando_texto(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *x = strtok(NULL, " ");
    char *y = strtok(NULL, " ");
    char *cor = strtok(NULL, " ");
    char *anc = strtok(NULL, " ");
    char *texto = strtok(NULL, "\n");

    if (!texto) texto = "";

    TEXTO t = criaTexto(id, atof(x), atof(y), cor, anc, texto, chao->estiloAtual);

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = TEXT;
    forma->data = t;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

static void executa_comando_textstyle(Chao_t *chao) {
    char *ff = strtok(NULL, " ");
    char *fw = strtok(NULL, " ");
    char *fs = strtok(NULL, " ");

    ESTILOTEXTO ts = criaEstiloTexto(ff, fw, atoi(fs));
    if (!ts) {
        printf("Erro ao criar EstiloTexto\n");
        return;
    }

    chao->estiloAtual = ts;

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = TEXT_STYLE;
    forma->data = ts;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

void processa_entrada_geo(ProcessaGeo p, char *linha) {
    Chao_t *chao = p;

    char *cmd = strtok(linha, " ");
    if (!cmd) return;

    if (!strcmp(cmd, "c")) executa_comando_circulo(chao);
    else if (!strcmp(cmd, "r")) executa_comando_retangulo(chao);
    else if (!strcmp(cmd, "l")) executa_comando_linha(chao);
    else if (!strcmp(cmd, "t")) executa_comando_texto(chao);
    else if (!strcmp(cmd, "ts")) executa_comando_textstyle(chao);
}

void desaloca_geo(ProcessaGeo p) {
    Chao_t *chao = p;

    while (!pilhaVazia(chao->pilha_para_free)) {
        Forma_t *forma = popPilha(chao->pilha_para_free);

        switch (forma->tipo) {
            case CIRCLE:
                desalocaCirculo(forma->data);
