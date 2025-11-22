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
#include <string.h>

enum TipoForma { CIRCLE, RECTANGLE, LINE, TEXT, TEXT_STYLE };
typedef enum TipoForma TipoForma;

typedef struct {
    Fila fila_formas;
    Pilha pilha_para_free;
    Fila fila_svg;
} Chao_t;

typedef struct {
    TipoForma tipo;
    void* data;
} Forma_t;

static void executa_comando_retangulo(Chao_t *chao);
static void executa_comando_circulo(Chao_t *chao);
static void executa_comando_linha(Chao_t *chao);
static void executa_comando_texto(Chao_t *chao);
static void executa_comando_textstyle(Chao_t *chao);
static void cria_fila_svg(Chao_t *chao, char* caminho_output, DadosDoArquivo fileData, const char *sufixo_comando);

Chao executa_comando_geo(DadosDoArquivo fileData, char *caminho_output, const char *sufixo_comando) {

    Chao_t *chao = malloc(sizeof(Chao_t));
    if (!chao) {
        printf("Erro de alocação\n");
        exit(1);
    }

    chao->fila_formas = criaFila();
    chao->pilha_para_free = criaPilha();
    chao->fila_svg = criaFila();

    while (!filaVazia(obter_fila_linhas(fileData))) {
        char *linha = (char*)dequeueFila(obter_fila_linhas(fileData));
        char *comando = strtok(linha, " ");

        if (strcmp(comando, "c") == 0)
            executa_comando_circulo(chao);

        else if (strcmp(comando, "r") == 0)
            executa_comando_retangulo(chao);

        else if (strcmp(comando, "l") == 0)
            executa_comando_linha(chao);

        else if (strcmp(comando, "t") == 0)
            executa_comando_texto(chao);

        else if (strcmp(comando, "ts") == 0)
            executa_comando_textstyle(chao);

        else
            printf("Comando inválido: %s\n", comando);
    }

    cria_fila_svg(chao, caminho_output, fileData, sufixo_comando);
    return chao;
}

Fila get_fila_chao(Chao chao) {
    return ((Chao_t*)chao)->fila_formas;
}

void desaloca_geo(Chao chao) {
    Chao_t *ch = (Chao_t*)chao;

    desalocaFila(ch->fila_formas);
    desalocaFila(ch->fila_svg);

    while (!pilhaVazia(ch->pilha_para_free)) {
        Forma_t *forma = popPilha(ch->pilha_para_free);

        switch (forma->tipo) {
            case CIRCLE:
                desalocaCirculo(forma->data);
                break;

            case RECTANGLE:
                desalocarRetangulo(forma->data);
                break;

            case LINE:
                desalocaLinha(forma->data);
                break;

            case TEXT:
                liberarTexto(forma->data);
                break;

            case TEXT_STYLE:
                desalocaEstiloTexto(forma->data);
                break;
        }
        free(forma);
    }

    desalocaPilha(ch->pilha_para_free);
    free(ch);
}

/* ========================================================================== */
/* ========================== EXECUTORES DE COMANDO ========================== */
/* ========================================================================== */

static void executa_comando_circulo(Chao_t *chao) {

    char *id = strtok(NULL, " ");
    char *X  = strtok(NULL, " ");
    char *Y  = strtok(NULL, " ");
    char *raio = strtok(NULL, " ");
    char *corB = strtok(NULL, " ");
    char *corP = strtok(NULL, " ");

    CIRCULO c = criaCirculo(
        atoi(id), atof(X), atof(Y),
        atof(raio), corP, corB
    );

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = CIRCLE;
    forma->data = c;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

static void executa_comando_retangulo(Chao_t *chao) {

    char *id = strtok(NULL, " ");
    char *X  = strtok(NULL, " ");
    char *Y  = strtok(NULL, " ");
    char *largura = strtok(NULL, " ");
    char *altura  = strtok(NULL, " ");
    char *corB = strtok(NULL, " ");
    char *corP = strtok(NULL, " ");

    RETANGULO r = criaRetangulo(
        atoi(id), atof(X), atof(Y),
        atof(altura), atof(largura),
        corB, corP
    );

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

    LINHA l = criaLinha(
        atoi(id), atof(x1), atof(y1),
        atof(x2), atof(y2), cor
    );

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = LINE;
    forma->data = l;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

static void executa_comando_texto(Chao_t *chao) {

    char *id = strtok(NULL, " ");
    char *x  = strtok(NULL, " ");
    char *y  = strtok(NULL, " ");
    char *corB = strtok(NULL, " ");
    char *corP = strtok(NULL, " ");
    char *anc = strtok(NULL, " ");
    char *txt = strtok(NULL, "");

    TEXTO t = novoTexto(
        atoi(id), atof(x), atof(y),
        corB, corP, *anc, txt
    );

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

    Forma_t *forma = malloc(sizeof(Forma_t));
    forma->tipo = TEXT_STYLE;
    forma->data = ts;

    enqueueFila(chao->fila_formas, forma);
    enqueueFila(chao->fila_svg, forma);
    pushPilha(chao->pilha_para_free, forma);
}

/* ========================================================================== */
/* ============================= GERAÇÃO DO SVG ============================ */
/* ========================================================================== */

static void cria_fila_svg(Chao_t *chao,
                          char* caminho_output,
                          DadosDoArquivo fileData,
                          const char *sufixo_comando)
{
    const char *nome_original = obter_nome_arquivo(fileData);

    char *nome = malloc(strlen(nome_original) + 1);
    strcpy(nome, nome_original);
    strtok(nome, ".");

    if (sufixo_comando != NULL) {
        strcat(nome, "-");
        strcat(nome, sufixo_comando);
    }

    char caminho[1024];
    snprintf(caminho, sizeof(caminho), "%s/%s.svg", caminho_output, nome);

    FILE *file = fopen(caminho, "w");
    if (!file) {
        printf("Erro ao abrir arquivo SVG\n");
        free(nome);
        return;
    }

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 2000 2000\">\n");

    while (!filaVazia(chao->fila_svg)) {

        Forma_t *forma = dequeueFila(chao->fila_svg);

        if (forma->tipo == CIRCLE) {
            CIRCULO c = forma->data;

            fprintf(file,
                "<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s'/>\n",
                getXCirculo(c), getYCirculo(c),
                getRaioCirculo(c), getCorPCirculo(c),
                getCorBCirculo(c)
            );
        }

        else if (forma->tipo == RECTANGLE) {
            RETANGULO r = forma->data;

            fprintf(file,
                "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' "
                "fill='%s' stroke='%s'/>\n",
                getXRetangulo(r), getYRetangulo(r),
                getLarguraRetangulo(r), getAlturaRetangulo(r),
                getCorPRetangulo(r), getCorBRetangulo(r)
            );
        }

        else if (forma->tipo == LINE) {
            LINHA l = forma->data;

            fprintf(file,
                "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                getX1Linha(l), getY1Linha(l),
                getX2Linha(l), getY2Linha(l),
                getCorLinha(l)
            );
        }

        else if (forma->tipo == TEXT) {
            TEXTO t = forma->data;

            char ancora = obterAncoraTexto(t);
            const char *anchor_svg = "start";

            if (ancora == 'm' || ancora == 'M') anchor_svg = "middle";
            else if (ancora == 'f' || ancora == 'F') anchor_svg = "end";

            fprintf(file,
                "<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                obterXTexto(t), obterYTexto(t),
                obterCorPTexto(t), obterCorBTexto(t),
                anchor_svg,
                obterConteudoTexto(t)
            );
        }
    }

    fprintf(file, "</svg>\n");
    fclose(file);
    free(nome);
}
