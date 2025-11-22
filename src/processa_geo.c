#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processa_geo.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "estilo_texto.h"
#include "fila.h"
#include "pilha.h"
#include "gerenciador_arquivos.h"

//---------------------------------------------------------
// Estruturas internas
//---------------------------------------------------------

typedef enum { CIRCLE, RECTANGLE, LINE, TEXT, TEXT_STYLE } TipoForma;

typedef struct {
    TipoForma tipo;
    void *data;
} Forma;

typedef struct {
    Fila fila_formas;       // saída final
    Pilha pilha_free;       // tudo que precisa ser desalocado
    ESTILOTEXTO estiloAtual;
} ChaoInterno;

//---------------------------------------------------------
// Funções auxiliares de criação de formas
//---------------------------------------------------------

static void criaCirculo_cmd(ChaoInterno *chao, char **tok) {
    char *id = tok[1];
    char *cx = tok[2];
    char *cy = tok[3];
    char *r  = tok[4];
    char *corb = tok[5];
    char *corp = tok[6];

    CIRCULO c = criaCirculo(id, atof(cx), atof(cy), atof(r), corb, corp);

    Forma *f = malloc(sizeof(Forma));
    f->tipo = CIRCLE;
    f->data = c;

    enqueueFila(chao->fila_formas, f);
    pushPilha(chao->pilha_free, f);
}

static void criaRetangulo_cmd(ChaoInterno *chao, char **tok) {
    char *id = tok[1];
    char *x  = tok[2];
    char *y  = tok[3];
    char *w  = tok[4];
    char *h  = tok[5];
    char *corb = tok[6];
    char *corp = tok[7];

    RETANGULO r = criaRetangulo(id, atof(x), atof(y), atof(w), atof(h), corb, corp);

    Forma *f = malloc(sizeof(Forma));
    f->tipo = RECTANGLE;
    f->data = r;

    enqueueFila(chao->fila_formas, f);
    pushPilha(chao->pilha_free, f);
}

static void criaLinha_cmd(ChaoInterno *chao, char **tok) {
    char *id = tok[1];
    char *x1 = tok[2];
    char *y1 = tok[3];
    char *x2 = tok[4];
    char *y2 = tok[5];
    char *cor = tok[6];

    LINHA l = criaLinha(id, atof(x1), atof(y1), atof(x2), atof(y2), cor);

    Forma *f = malloc(sizeof(Forma));
    f->tipo = LINE;
    f->data = l;

    enqueueFila(chao->fila_formas, f);
    pushPilha(chao->pilha_free, f);
}

static void criaTexto_cmd(ChaoInterno *chao, char *linha_original) {

    // Pega tokens iniciais
    char *tok = strtok(linha_original, " ");
    char *id  = strtok(NULL, " ");
    char *x   = strtok(NULL, " ");
    char *y   = strtok(NULL, " ");
    char *cor = strtok(NULL, " ");
    char *anc = strtok(NULL, " ");

    // Texto é o resto da linha
    char *texto = strtok(NULL, "\n");
    if (!texto) texto = "";

    TEXTO t = criaTexto(id, atof(x), atof(y), cor, anc, texto, chao->estiloAtual);

    Forma *f = malloc(sizeof(Forma));
    f->tipo = TEXT;
    f->data = t;

    enqueueFila(chao->fila_formas, f);
    pushPilha(chao->pilha_free, f);
}

static void criaTextStyle_cmd(ChaoInterno *chao, char **tok) {
    char *ff = tok[1];
    char *fw = tok[2];
    char *fs = tok[3];

    ESTILOTEXTO ts = criaEstiloTexto(ff, fw, atoi(fs));
    if (!ts) {
        printf("Erro ao criar estilo de texto\n");
        return;
    }

    chao->estiloAtual = ts;

    Forma *f = malloc(sizeof(Forma));
    f->tipo = TEXT_STYLE;
    f->data = ts;

    enqueueFila(chao->fila_formas, f);
    pushPilha(chao->pilha_free, f);
}

//---------------------------------------------------------
// Função principal exigida pelo .h
//---------------------------------------------------------

Chao executa_comando_geo(DadosDoArquivo fileData, char *caminho_output, const char *sufixo_comando) {
    (void)caminho_output; 
    (void)sufixo_comando;

    ChaoInterno *chao = malloc(sizeof(ChaoInterno));
    chao->fila_formas = criaFila();
    chao->pilha_free = criaPilha();
    chao->estiloAtual = NULL;

    for (int i = 0; i < fileData->num_linhas; i++) {

        char buffer[512];
        strcpy(buffer, fileData->linhas[i]);

        char *cmd = strtok(buffer, " ");
        if (!cmd) continue;

        // separa tokens
        char *tok[15];
        int qtd = 0;
        tok[qtd++] = cmd;

        char *p = NULL;
        while ((p = strtok(NULL, " ")) != NULL && qtd < 15) {
            tok[qtd++] = p;
        }

        if (!strcmp(cmd, "c") && qtd >= 7) {
            criaCirculo_cmd(chao, tok);
        }
        else if (!strcmp(cmd, "r") && qtd >= 8) {
            criaRetangulo_cmd(chao, tok);
        }
        else if (!strcmp(cmd, "l") && qtd >= 7) {
            criaLinha_cmd(chao, tok);
        }
        else if (!strcmp(cmd, "t")) {
            char original[512];
            strcpy(original, fileData->linhas[i]);
            criaTexto_cmd(chao, original);
        }
        else if (!strcmp(cmd, "ts") && qtd >= 4) {
            criaTextStyle_cmd(chao, tok);
        }
    }

    return chao;
}

//---------------------------------------------------------
// Getter
//---------------------------------------------------------

Fila get_fila_chao(Chao chao) {
    return ((ChaoInterno*)chao)->fila_formas;
}

//---------------------------------------------------------
// Liberação de memória
//---------------------------------------------------------

void desaloca_geo(Chao chao) {
    ChaoInterno *c = (ChaoInterno*) chao;

    while (!pilhaVazia(c->pilha_free)) {

        Forma *f = popPilha(c->pilha_free);

        switch (f->tipo) {
            case CIRCLE:      desalocaCirculo(f->data);      break;
            case RECTANGLE:   desalocaRetangulo(f->data);    break;
            case LINE:        desalocaLinha(f->data);        break;
            case TEXT:        desalocaTexto(f->data);        break;
            case TEXT_STYLE:  desalocaEstiloTexto(f->data);  break;
        }
        free(f);
    }

    desalocaFila(c->fila_formas, NULL);
    desalocaPilha(c->pilha_free);
    free(c);
}
