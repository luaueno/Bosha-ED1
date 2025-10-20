/*
================================================================================
Arquivo: parser_argumentos.c
--------------------------------------------------------------------------------
Descrição:
  Módulo responsável por processar e interpretar os argumentos de linha de comando
  passados ao programa. Permite obter valores associados a opções e identificar
  sufixos de comando.

Funções principais:
  - obterValorOpcao: Retorna o valor associado a uma opção passada por linha de comando.
  - obterSufixoComando: Retorna o sufixo final do comando (último argumento sem '-').
================================================================================
*/

#include "parser_argumentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Retorna o valor associado a uma opção do tipo -opcao.
 *
 * Exemplo:
 *   ./programa -f arquivo.txt → obterValorOpcao(argc, argv, "f") → "arquivo.txt"
 *
 * @param argc Número de argumentos recebidos.
 * @param argv Vetor de strings com os argumentos.
 * @param nomeOpcao Nome da opção sem o prefixo '-'.
 * @return char* Valor associado à opção, ou NULL se não encontrado.
 */
char* obterValorOpcao(int argc, char* argv[], const char* nomeOpcao) {
    char formatoOpcao[64];
    snprintf(formatoOpcao, sizeof(formatoOpcao), "-%s", nomeOpcao);

    for (int i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], formatoOpcao) == 0) {
            if (argv[i + 1] == NULL || argv[i + 1][0] == '-')
                return NULL;
            return argv[i + 1];
        }
    }
    return NULL;
}

/**
 * @brief Retorna o sufixo de comando (último argumento que não começa com '-').
 *
 * Exemplo:
 *   ./programa -f arquivo.txt saida → retorna "saida"
 *
 * @param argc Número de argumentos.
 * @param argv Vetor de argumentos.
 * @return char* Ponteiro para o sufixo, ou NULL se não houver.
 */
char* obterSufixoComando(int argc, char* argv[]) {
    char** argvCopia = malloc(argc * sizeof(char*));
    if (argvCopia == NULL)
        return NULL;

    for (int i = 0; i < argc; i++) {
        argvCopia[i] = argv[i];
    }

    int novoArgc = argc;

    // Remove pares de opções e valores
    for (int i = 1; i < novoArgc - 1; i++) {
        if (argvCopia[i][0] == '-') {
            if (argvCopia[i + 1][0] != '-') {
                for (int j = i; j < novoArgc - 2; j++) {
                    argvCopia[j] = argvCopia[j + 2];
                }
                novoArgc -= 2;
                i--;
            }
        }
    }

    char* sufixo = NULL;
    if (novoArgc == 2) {
        sufixo = argvCopia[novoArgc - 1];
    } else if (novoArgc > 2) {
        printf("Erro: mais de um sufixo encontrado.\n");
        free(argvCopia);
        exit(EXIT_FAILURE);
    }

    free(argvCopia);
    return sufixo;
}
