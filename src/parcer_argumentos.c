#include "parser_argumentos.h"
#include <stdio.h>
#include <string.h>

static const char* obterValor(int argc, char* argv[], const char* opcao) {
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], opcao) == 0) {
            if (argv[i + 1][0] == '-') return NULL;
            return argv[i + 1];
        }
    }
    return NULL;
}

Argumentos parse_argumentos(int argc, char *argv[]) {
    Argumentos args;
    args.validos = 1;

    args.arquivo_geo = obterValor(argc, argv, "-geo");
    args.arquivo_qry = obterValor(argc, argv, "-qry");
    args.pasta_saida = obterValor(argc, argv, "-o");

    if (!args.arquivo_geo || !args.arquivo_qry || !args.pasta_saida) {
        printf("Erro: argumentos faltando.\n");
        args.validos = 0;
    }

    return args;
}
