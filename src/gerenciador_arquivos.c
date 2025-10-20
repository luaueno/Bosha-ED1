/*
 * gerenciador_arquivos.c
 *
 * Módulo responsável por realizar a leitura e gerenciamento de arquivos de texto,
 * armazenando suas linhas em uma fila (para processamento sequencial) e em uma pilha
 * (para posterior liberação de memória).
 *
 * Este módulo implementa funções para criação, leitura, acesso e destruição de
 * estruturas que representam o conteúdo de um arquivo. O objetivo é fornecer uma
 * interface simples e segura para o controle de dados lidos de arquivos.
 */

#include "gerenciador_arquivos.h"
#include "fila.h"
#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================================
 * Estruturas internas (privadas)
 * =========================================================================
 */

typedef struct {
    const char *caminhoArquivo;        // Caminho completo do arquivo
    const char *nomeArquivo;           // Nome do arquivo (sem o caminho)
    Fila filaDeLinhas;                 // Fila que armazena as linhas lidas
    Pilha pilhaLinhasParaLiberar;      // Pilha usada para liberar memória das linhas
} DadosDoArquivoSt;

typedef struct {
    Fila filaDeLinhas;
    Pilha pilhaLinhasParaLiberar;
} EstruturasDeLinhas;

/* =========================================================================
 * Funções auxiliares (privadas)
 * =========================================================================
 */

/// Lê uma linha do arquivo usando fgets e remove o '\n' final, se existir.
static char* lerLinha(FILE *arquivo, char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, arquivo) == NULL)
        return NULL;

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    return buffer;
}

/// Duplica uma string, retornando uma cópia alocada dinamicamente.
static char* duplicarString(const char *s) {
    if (s == NULL)
        return NULL;

    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup)
        strcpy(dup, s);

    return dup;
}

/// Lê todas as linhas de um arquivo e as insere na fila e pilha correspondentes.
static EstruturasDeLinhas* carregarLinhasArquivo(const char *caminhoArquivo) {
    EstruturasDeLinhas *estruturas = malloc(sizeof(EstruturasDeLinhas));
    if (!estruturas) {
        printf("[ERRO] Falha ao alocar EstruturasDeLinhas.\n");
        return NULL;
    }

    Fila fila = criaFila();
    Pilha pilha = criaPilha();
    if (!fila || !pilha) {
        desalocaFila(fila);
        desalocaPilha(pilha);
        free(estruturas);
        return NULL;
    }

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo) {
        printf("[ERRO] Não foi possível abrir o arquivo: %s\n", caminhoArquivo);
        desalocaFila(fila);
        desalocaPilha(pilha);
        free(estruturas);
        return NULL;
    }

    char buffer[1024];
    while (lerLinha(arquivo, buffer, sizeof(buffer))) {
        char *linha = duplicarString(buffer);
        enqueueFila(fila, linha);
        pushPilha(pilha, linha);
    }

    fclose(arquivo);

    estruturas->filaDeLinhas = fila;
    estruturas->pilhaLinhasParaLiberar = pilha;
    return estruturas;
}

/* =========================================================================
 * Funções principais (públicas)
 * =========================================================================
 */

DadosDoArquivo criarDadosArquivo(const char *caminhoArquivo) {
    if (!caminhoArquivo)
        return NULL;

    DadosDoArquivoSt *dados = malloc(sizeof(DadosDoArquivoSt));
    if (!dados) {
        printf("[ERRO] Falha ao alocar DadosDoArquivo.\n");
        return NULL;
    }

    dados->caminhoArquivo = caminhoArquivo;
    dados->nomeArquivo =
        strrchr(caminhoArquivo, '/') ? strrchr(caminhoArquivo, '/') + 1 : caminhoArquivo;

    EstruturasDeLinhas *estruturas = carregarLinhasArquivo(caminhoArquivo);
    if (!estruturas) {
        free(dados);
        return NULL;
    }

    dados->filaDeLinhas = estruturas->filaDeLinhas;
    dados->pilhaLinhasParaLiberar = estruturas->pilhaLinhasParaLiberar;
    free(estruturas);

    return (DadosDoArquivo)dados;
}

void destruirDadosArquivo(DadosDoArquivo dadosArquivo) {
    if (!dadosArquivo)
        return;

    DadosDoArquivoSt *dados = (DadosDoArquivoSt *)dadosArquivo;

    // Libera todas as linhas armazenadas na pilha
    while (!pilhaVazia(dados->pilhaLinhasParaLiberar)) {
        char *linha = popPilha(dados->pilhaLinhasParaLiberar);
        if (linha)
            free(linha);
    }

    desalocaPilha(dados->pilhaLinhasParaLiberar);
    desalocaFila(dados->filaDeLinhas);
    free(dados);
}

/* =========================================================================
 * Funções de acesso (getters)
 * =========================================================================
 */

const char* obterCaminhoArquivo(DadosDoArquivo dadosArquivo) {
    if (!dadosArquivo)
        return NULL;
    return ((DadosDoArquivoSt *)dadosArquivo)->caminhoArquivo;
}

const char* obterNomeArquivo(DadosDoArquivo dadosArquivo) {
    if (!dadosArquivo)
        return NULL;
    return ((DadosDoArquivoSt *)dadosArquivo)->nomeArquivo;
}

Fila obterFilaLinhas(DadosDoArquivo dadosArquivo) {
    if (!dadosArquivo)
        return NULL;
    return ((DadosDoArquivoSt *)dadosArquivo)->filaDeLinhas;
}
