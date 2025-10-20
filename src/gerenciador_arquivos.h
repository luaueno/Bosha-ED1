/*
================================================================================
Arquivo: gerenciador_arquivos.h
--------------------------------------------------------------------------------
Descrição:
  Header do módulo "Gerenciador de Arquivos", responsável por ler arquivos texto,
  armazenar suas linhas em uma fila e em uma pilha, e gerenciar a liberação
  de memória dessas estruturas.

  O tipo de dado principal, `DadosDoArquivo`, é opaco (incompleto) e deve ser
  manipulado apenas através das funções desta interface.

Dependências:
  - fila.h
  - pilha.h

Autor: (adicione seu nome)
Data: (adicione a data atual)
================================================================================
*/

#ifndef GERENCIADOR_ARQUIVOS_H
#define GERENCIADOR_ARQUIVOS_H

#include "fila.h"
#include "pilha.h"

/*==============================================================================
  Definições de tipos
==============================================================================*/

/// Tipo opaco que representa os dados de um arquivo.
/// A estrutura real é definida apenas em gerenciador_arquivos.c.
typedef void* DadosDoArquivo;

/*==============================================================================
  Funções públicas da interface
==============================================================================*/

/**
 * @brief Cria um novo objeto que representa um arquivo e lê todas as suas linhas.
 * 
 * O arquivo é aberto em modo leitura e cada linha é armazenada tanto em uma fila
 * quanto em uma pilha, permitindo diferentes formas de acesso.
 * 
 * @param caminhoArquivo Caminho completo do arquivo a ser lido.
 * @return DadosDoArquivo Ponteiro genérico para o objeto criado, ou NULL em caso de erro.
 */
DadosDoArquivo criar_dados_arquivo(const char *caminhoArquivo);

/**
 * @brief Libera toda a memória associada ao objeto DadosDoArquivo.
 * 
 * Inclui a desalocação da fila, da pilha e das strings das linhas armazenadas.
 * 
 * @param dadosArquivo Ponteiro para o objeto a ser destruído. Se for NULL, nada é feito.
 */
void destruir_dados_arquivo(DadosDoArquivo dadosArquivo);

/**
 * @brief Retorna o caminho completo do arquivo original.
 * 
 * @param dadosArquivo Ponteiro para o objeto DadosDoArquivo.
 * @return const char* Caminho do arquivo, ou NULL se dadosArquivo for inválido.
 */
const char *obter_caminho_arquivo(const DadosDoArquivo dadosArquivo);

/**
 * @brief Retorna apenas o nome do arquivo (sem o caminho).
 * 
 * @param dadosArquivo Ponteiro para o objeto DadosDoArquivo.
 * @return const char* Nome do arquivo, ou NULL se dadosArquivo for inválido.
 */
const char *obter_nome_arquivo(const DadosDoArquivo dadosArquivo);

/**
 * @brief Retorna a fila com as linhas do arquivo.
 * 
 * @param dadosArquivo Ponteiro para o objeto DadosDoArquivo.
 * @return Fila Estrutura Fila contendo as linhas do arquivo, ou NULL se dadosArquivo for inválido.
 */
Fila obter_fila_linhas(const DadosDoArquivo dadosArquivo);

#endif
