/*
================================================================================
Arquivo: parser_argumentos.h
--------------------------------------------------------------------------------
Descrição:
    Este módulo é responsável por interpretar os argumentos de linha de comando
    passados ao programa. Ele identifica e valida as opções:

        -geo <arquivo.geo>
        -qry <arquivo.qry>
        -o <pasta_saida>

    O objetivo é fornecer uma estrutura organizada que permita ao programa
    principal (main.c) acessar facilmente os argumentos fornecidos.
================================================================================
*/

#ifndef PARSER_ARGUMENTOS_H
#define PARSER_ARGUMENTOS_H

/**
 * ============================================================================
 * Estrutura: Argumentos
 * ----------------------------------------------------------------------------
 * Representa os parâmetros fornecidos ao programa via linha de comando.
 *
 * Campos:
 *  - validos:
 *        Indica se os argumentos foram fornecidos corretamente.
 *        1  = argumentos corretos
 *        0  = algo faltando ou com erro
 *
 *  - arquivo_geo:
 *        Caminho para o arquivo .geo fornecido pela opção:
 *            -geo caminho.geo
 *
 *  - arquivo_qry:
 *        Caminho para o arquivo .qry fornecido pela opção:
 *            -qry caminho.qry
 *
 *  - pasta_saida:
 *        Caminho da pasta onde os resultados devem ser gerados:
 *            -o pasta/
 *
 * Obs: Todos os ponteiros armazenam strings já presentes em argv[]
 *      (não é necessário desalocar manualmente).
 * ============================================================================
 */
typedef struct {
    int validos;               ///< 1 se argumentos são válidos, 0 caso contrário
    const char *arquivo_geo;   ///< Caminho do arquivo .geo
    const char *arquivo_qry;   ///< Caminho do arquivo .qry
    const char *pasta_saida;   ///< Caminho da pasta de saída
} Argumentos;


/**
 * ============================================================================
 * Função: parse_argumentos
 * ----------------------------------------------------------------------------
 * Analisa os argumentos fornecidos ao programa e retorna uma estrutura
 * Argumentos preenchida.
 *
 * Funcionamento:
 *  - Lê argv[] procurando pelas opções obrigatórias:
 *        -geo <arquivo.geo>
 *        -qry <arquivo.qry>
 *        -o <pasta_saida>
 *
 *  - Se estiver tudo correto, retorna Argumentos com:
 *        args.validos = 1
 *
 *  - Caso falte alguma opção, retorna:
 *        args.validos = 0
 *
 * Exemplo de uso:
 *
 *      Argumentos args = parse_argumentos(argc, argv);
 *      if (!args.validos) {
 *          printf("Erro nos argumentos.\n");
 *          return 1;
 *      }
 *
 * ============================================================================
 *
 * @param argc  Número total de argumentos
 * @param argv  Vetor contendo os argumentos
 *
 * @return Estrutura Argumentos preenchida com os valores encontrados
 */
Argumentos parse_argumentos(int argc, char *argv[]);

#endif
