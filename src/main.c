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
    DadosDoArquivo geo = criar_dados_arquivo(arquivo_geo);
    DadosDoArquivo qry = criar_dados_arquivo(arquivo_qry);

    if (!geo || !qry) {
        printf("Erro ao ler arquivos.\n");
        return 1;
    }

    // ---------- PROCESSAMENTO GEO ---------- //
    Chao chao = executa_comando_geo(geo, (char*)pasta_saida, "geo");

    if (!chao) {
        printf("Erro ao processar arquivo GEO.\n");
        destruir_dados_arquivo(geo);
        destruir_dados_arquivo(qry);
        return 1;
    }

    // ---------- EXECUÇÃO DAS QUERIES ---------- //
    ProcessaQry qry_resultado = executaProcessaQry(qry, geo, chao, pasta_saida);

    if (!qry_resultado) {
        printf("Erro ao processar arquivo QRY.\n");
        desaloca_geo(chao);
        destruir_dados_arquivo(geo);
        destruir_dados_arquivo(qry);
        return 1;
    }

    printf("Processamento concluído. Arquivos gerados em: %s\n", pasta_saida);

    // ---------- LIMPEZA ---------- //
    desalocaProcessaQry(qry_resultado);
    desaloca_geo(chao);
    destruir_dados_arquivo(geo);
    destruir_dados_arquivo(qry);

    return 0;
}
