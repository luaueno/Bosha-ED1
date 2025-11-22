#include "processa_geo.h"
#include "fila.h"
#include "pilha.h"
#include "gerenciador_arquivos.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "estilo_texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { CIRCLE, RECTANGLE, LINE, TEXT, TEXT_STYLE } TipoForma;

typedef struct {
    Fila fila_formas;
    Pilha pilha_para_free;
    Fila fila_svg;
} Chao_t;

typedef struct {
    TipoForma tipo;
    void *data;
} Forma_t;

/* =================== AUXILIARES =================== */
static Forma_t *cria_forma(TipoForma tipo, void *data, Chao_t *chao) {
    if (!data || !chao) return NULL;

    Forma_t *forma = malloc(sizeof(Forma_t));
    if (!forma) return NULL;

    forma->tipo = tipo;
    forma->data = data;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
    return forma;
}

/* =================== EXECUTORES =================== */
static void executa_comando_circulo(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *X  = strtok(NULL, " ");
    char *Y  = strtok(NULL, " ");
    char *raio = strtok(NULL, " ");
    char *corB = strtok(NULL, " ");
    char *corP = strtok(NULL, " ");
    if (!id || !X || !Y || !raio || !corB || !corP) return;

    CIRCULO c = criaCirculo(atoi(id), atof(X), atof(Y), atof(raio), corP, corB);
    cria_forma(CIRCLE, c, chao);
}

static void executa_comando_retangulo(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *X  = strtok(NULL, " ");
    char *Y  = strtok(NULL, " ");
    char *largura = strtok(NULL, " ");
    char *altura  = strtok(NULL, " ");
    char *corB = strtok(NULL, " ");
    char *corP = strtok(NULL, " ");
    if (!id || !X || !Y || !largura || !altura || !corB || !corP) return;

    RETANGULO r = criaRetangulo(atoi(id), atof(X), atof(Y), atof(largura), atof(altura), corB, corP);
    cria_forma(RECTANGLE, r, chao);
}

static void executa_comando_linha(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *x1 = strtok(NULL, " ");
    char *y1 = strtok(NULL, " ");
    char *x2 = strtok(NULL, " ");
    char *y2 = strtok(NULL, " ");
    char *cor = strtok(NULL, " ");
    if (!id || !x1 || !y1 || !x2 || !y2 || !cor) return;

    LINHA l = criaLinha(atoi(id), atof(x1), atof(y1), atof(x2), atof(y2), cor);
    cria_forma(LINE, l, chao);
}

static void executa_comando_texto(Chao_t *chao) {
    char *id = strtok(NULL, " ");
    char *x  = strtok(NULL, " ");
    char *y  = strtok(NULL, " ");
    char *corB = strtok(NULL, " ");
    char *corP = strtok(NULL, " ");
    char *anc = strtok(NULL, " ");
    char *txt = strtok(NULL, "");
    if (!id || !x || !y || !corB || !corP || !anc || !txt) return;

    TEXTO t = novoTexto(atoi(id), atof(x), atof(y), corB, corP, *anc, txt);
    cria_forma(TEXT, t, chao);
}

static void executa_comando_textstyle(Chao_t *chao) {
    char *ff = strtok(NULL, " ");
    char *fw = strtok(NULL, " ");
    char *fs = strtok(NULL, " ");
    if (!ff || !fw || !fs) return;

    ESTILOTEXTO ts = criaEstiloTexto(ff, fw, atoi(fs));
    cria_forma(TEXT_STYLE, ts, chao);
}

/* =================== GERAÇÃO DO SVG =================== */
static void cria_fila_svg(Chao_t *chao, char *caminho_output, DadosDoArquivo fileData, const char *sufixo_comando) {
    if (!chao || !caminho_output) return;

    const char *nome_original = obter_nome_arquivo(fileData);
    if (!nome_original) return;

    char nome[256];
    strncpy(nome, nome_original, sizeof(nome)-1);
    nome[sizeof(nome)-1] = '\0';
    strtok(nome, ".");

    if (sufixo_comando) {
        strncat(nome, "-", sizeof(nome)-strlen(nome)-1);
        strncat(nome, sufixo_comando, sizeof(nome)-strlen(nome)-1);
    }

    char caminho[1024];
    snprintf(caminho, sizeof(caminho), "%s/%s.svg", caminho_output, nome);

    FILE *file = fopen(caminho, "w");
    if (!file) return;

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 2000 2000\">\n");

    while (!filaVazia(chao->fila_svg)) {
        Forma_t *f = dequeueFila(chao->fila_svg);
        if (!f) continue;

        switch (f->tipo) {
            case CIRCLE: {
                CIRCULO c = f->data;
                fprintf(file,
                    "<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s'/>\n",
                    getXCirculo(c), getYCirculo(c), getRaioCirculo(c),
                    getCorPCirculo(c), getCorBCirculo(c));
                break;
            }
            case RECTANGLE: {
                RETANGULO r = f->data;
                fprintf(file,
                    "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='%s' stroke='%s'/>\n",
                    getXRetangulo(r), getYRetangulo(r),
                    getLarguraRetangulo(r), getAlturaRetangulo(r),
                    getCorPRetangulo(r), getCorBRetangulo(r));
                break;
            }
            case LINE: {
                LINHA l = f->data;
                fprintf(file,
                    "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                    getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l),
                    getCorLinha(l));
                break;
            }
            case TEXT: {
                TEXTO t = f->data;
                char ancora = obterAncoraTexto(t);
                const char *anchor_svg = (ancora=='m'||ancora=='M')?"middle":(ancora=='f'||ancora=='F')?"end":"start";
                fprintf(file,
                    "<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                    obterXTexto(t), obterYTexto(t),
                    obterCorPTexto(t), obterCorBTexto(t),
                    anchor_svg, obterConteudoTexto(t));
                break;
            }
            default: break;
        }
    }

    fprintf(file, "</svg>\n");
    fclose(file);
}

/* =================== FUNÇÕES PÚBLICAS =================== */
Chao executa_geo(DadosDoArquivo fileData, char *caminho_output, const char *sufixo_comando) {
    Chao_t *chao = malloc(sizeof(Chao_t));
    if (!chao) exit(1);

    chao->fila_formas = criaFila();
    chao->pilha_para_free = criaPilha();
    chao->fila_svg = criaFila();

    while (!filaVazia(obter_fila_linhas(fileData))) {
        char *linha = (char*)dequeueFila(obter_fila_linhas(fileData));
        if (!linha) continue;

        char *comando = strtok(linha, " \r\n\t");
        if (!comando) continue;

        if (strcmp(comando, "c")==0) executa_comando_circulo(chao);
        else if (strcmp(comando, "r")==0) executa_comando_retangulo(chao);
        else if (strcmp(comando, "l")==0) executa_comando_linha(chao);
        else if (strcmp(comando, "t")==0) executa_comando_texto(chao);
        else if (strcmp(comando, "ts")==0) executa_comando_textstyle(chao);
        else printf("Comando inválido: %s\n", comando);
    }

    cria_fila_svg(chao, caminho_output, fileData, sufixo_comando);
    return chao;
}

Fila get_fila_chao(Chao chao) { return ((Chao_t*)chao)->fila_formas; }

void desaloca_geo(Chao chao) {
    Chao_t *ch = (Chao_t*)chao;
    desalocaFila(ch->fila_formas);
    desalocaFila(ch->fila_svg);

    while (!pilhaVazia(ch->pilha_para_free)) {
        Forma_t *f = popPilha(ch->pilha_para_free);
        if (!f) continue;

        switch(f->tipo) {
            case CIRCLE: desalocaCirculo(f->data); break;
            case RECTANGLE: desalocarRetangulo(f->data); break;
            case LINE: desalocaLinha(f->data); break;
            case TEXT: liberarTexto(f->data); break;
            case TEXT_STYLE: desalocaEstiloTexto(f->data); break;
        }
        free(f);
    }
    desalocaPilha(ch->pilha_para_free);
    free(ch);
}
