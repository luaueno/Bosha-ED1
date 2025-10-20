#ifndef PROCESSA_GEO_H
#define PROCESSA_GEO_H

#include "fila.h"
#include "pilha.h"
#include "leitor_arquivos.h"

// Define tipo opaco para Chao
typedef void* Chao;

/**
 * @brief Executa os comandos do arquivo .geo, cria filas e pilhas correspondentes,
 *        e gera o arquivo SVG de saída.
 * 
 * @param fileData Estrutura contendo os dados lidos do arquivo .geo.
 * @param caminho_output Diretório de saída para o arquivo SVG.
 * @param sufixo_comando Sufixo adicional para o nome do arquivo de saída (ex: "geo").
 * 
 * @return Chao Estrutura interna contendo filas e pilhas criadas durante a execução.
 */
Chao executa_comando_geo(DadosDoArquivo fileData, char *caminho_output, const char *sufixo_comando);

/**
 * @brief Retorna a fila principal de formas do "chão".
 * 
 * @param chao Estrutura principal retornada por executa_comando_geo.
 * @return Fila Fila de formas gráficas (Círculo, Retângulo, Linha, Texto, etc.)
 */
Fila get_fila_chao(Chao chao);

/**
 * @brief Desaloca toda a memória alocada durante o processamento do arquivo .geo.
 * 
 * @param chao Estrutura retornada por executa_comando_geo.
 */
void desaloca_geo(Chao chao);

#endif
