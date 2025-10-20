/*
================================================================================
Arquivo: parser_argumentos.h
--------------------------------------------------------------------------------
Descrição:
  Header do módulo responsável por processar os argumentos de linha de comando
  passados ao programa. Permite buscar valores associados a opções e extrair
  o sufixo do comando.

Autor: (adicione seu nome)
Data: (adicione a data atual)
================================================================================
*/

#ifndef PARSER_ARGUMENTOS_H
#define PARSER_ARGUMENTOS_H

/**
 * @brief Retorna o valor associado a uma opção do tipo -opcao.
 *
 * Exemplo:
 *   ./programa -i entrada.txt → obterValorOpcao(argc, argv, "i") → "entrada.txt"
 *
 * @param argc Número total de argumentos passados.
 * @param argv Vetor com os argumentos.
 * @param nomeOpcao Nome da opção sem o caractere '-'.
 * @return char* Ponteiro para a string com o valor associado, ou NULL se não existir.
 */
char* obterValorOpcao(int argc, char* argv[], const char* nomeOpcao);

/**
 * @brief Retorna o sufixo de comando (último argumento sem prefixo '-').
 *
 * Exemplo:
 *   ./programa -f arquivo.txt saida → retorna "saida"
 *
 * @param argc Número total de argumentos passados.
 * @param argv Vetor com os argumentos.
 * @return char* Ponteiro para o sufixo encontrado, ou NULL se não houver.
 */
char* obterSufixoComando(int argc, char* argv[]);

#endif
