#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"
#include "processa_qry.h"
#include "processa_geo.h"
#include "gerenciador_arquivos.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "estilo_texto.h"
#include "parcer_argumentos.h"

int main(int argc, char *argv[]) {

    // ---------- PARSING DE ARGUMENTOS ---------- //
    Argumentos args = parse_argumentos(argc, argv);
    if (!args.validos) {
        printf("Uso: %s -geo <arquivo.geo> -qry <arquivo.qry> -o <pasta_saida>\n", argv[0]);
        return 1;
    }

    const char *arquivo_geo = args.arquivo_geo;
    const char *arquivo_qry = args.arquivo_qry;
    const char *pasta_saida = args.pasta_saida;

    // ---------- LEITURA DOS ARQUIVOS ---------- //
    DadosDoArquivo geo = le_arquivo(arquivo_geo);
    DadosDoArquivo qry_linhas = le_arquivo(arquivo_qry);

    if (!geo.linhas || !qry_linhas.linhas) {
        printf("Erro ao ler arquivos.\n");
        return 1;
    }

    // ---------- PROCESSAMENTO GEO ---------- //
    Chao chao = processa_geo(geo);

    if (!chao) {
        printf("Erro ao processar arquivo GEO.\n");
        return 1;
    }

    // ---------- EXECUÇÃO DAS QUERIES ---------- //
    Qry qry_resultado = executa_qry(qry_linhas, geo, chao, pasta_saida);

    if (!qry_resultado) {
        printf("Erro ao processar arquivo QRY.\n");
        desaloca_chao(chao);
        desaloca_geo(geo);
        return 1;
    }

    printf("Processamento concluído. Arquivos gerados em: %s\n", pasta_saida);

    // ---------- LIMPEZA ---------- //
    desaloca_qry(qry_resultado);
    desaloca_chao(chao);
    desaloca_geo(geo);

    return 0;
}
