#include "gerenciador_arquivos.h"
#include "fila.h"
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *caminho;
    const char *nome;
    Fila linhas;
    Pilha pilhaLinhas;
} DadosDoArquivoSt;

static char* lerLinha(FILE *f, char *buf, size_t tam) {
    if (!fgets(buf, tam, f)) return NULL;
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n')
        buf[len-1] = '\0';
    return buf;
}

static char* dupString(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) strcpy(d, s);
    return d;
}

DadosDoArquivo le_arquivo(const char *caminho) {
    if (!caminho) return NULL;

    FILE *arq = fopen(caminho, "r");
    if (!arq) {
        printf("[ERRO] Não foi possível abrir %s\n", caminho);
        return NULL;
    }

    DadosDoArquivoSt *dados = malloc(sizeof(DadosDoArquivoSt));
    if (!dados) {
        fclose(arq);
        return NULL;
    }

    dados->caminho = caminho;
    dados->nome = strrchr(caminho, '/') ? strrchr(caminho, '/') + 1 : caminho;

    dados->linhas = novaFila();
    dados->pilhaLinhas = criaPilha();

    if (!dados->linhas || !dados->pilhaLinhas) {
        printf("[ERRO] Falha ao criar fila ou pilha.\n");
        if (dados->linhas) liberarFila(dados->linhas);
        if (dados->pilhaLinhas) desalocaPilha(dados->pilhaLinhas);
        free(dados);
        fclose(arq);
        return NULL;
    }

    char buffer[2048];
    while (lerLinha(arq, buffer, sizeof(buffer))) {
        char *linha = dupString(buffer);
        enfileirar(dados->linhas, linha);
        pushPilha(dados->pilhaLinhas, linha);
    }

    fclose(arq);
    return dados;
}

void desaloca_geo(DadosDoArquivo dados) {
    if (!dados) return;

    DadosDoArquivoSt *d = (DadosDoArquivoSt *)dados;

    while (!pilhaVazia(d->pilhaLinhas)) {
        char *linha = popPilha(d->pilhaLinhas);
        if (linha) free(linha);
    }

    desalocaPilha(d->pilhaLinhas);
    liberarFila(d->linhas);

    free(d);
}

Fila obter_linhas(DadosDoArquivo dados) {
    if (!dados) return NULL;
    return ((DadosDoArquivoSt *)dados)->linhas;
}
