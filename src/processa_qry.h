#ifndef PROCESSA_QRY_H
#define PROCESSA_QRY_H

#include "gerenciador_arquivos.h"
#include "processa_geo.h" 

typedef void *ProcessaQry;

/**
 * @brief Executa os comandos contidos no arquivo QRY, utilizando os dados do GEO e o chao de formas.
 * 
 * @param dadosQry Dados do arquivo QRY.
 * @param dadosGeo Dados do arquivo GEO.
 * @param chao Estrutura de chao contendo formas já processadas.
 * @param caminho_output Caminho onde os arquivos de saída serão gerados.
 * @return ProcessaQry Ponteiro para a estrutura interna do QRY processado.
 */
ProcessaQry executaProcessaQry(DadosDoArquivo dadosQry, DadosDoArquivo dadosGeo, Chao chao, const char *caminho_output);

/**
 * @brief Libera toda a memória associada a um QRY processado.
 * 
 * @param qry Ponteiro retornado por executaProcessaQry.
 */
void desalocaProcessaQry(ProcessaQry qry);

#endif
