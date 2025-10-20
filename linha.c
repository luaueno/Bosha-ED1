#ifndef LINHA_H
#define LINHA_H

#include <stdlib.h>

/**
 * @file linha.h
 * @brief Módulo para representar linhas.
 *
 * Define uma estrutura opaca para linhas com coordenadas iniciais e finais,
 * cor da linha e ID. Fornece funções para criação, acesso, modificação,
 * cálculo de "área" (comprimento) e desalocação.
 */

typedef void* LINHA; /**< Tipo opaco para linha */

/* ======== CRIAÇÃO ======== */
LINHA novaLinha(int id, float x1, float y1, float x2, float y2, char* cor);

/* ======== MÉTODOS GET ======== */
int obterIDLinha(LINHA l);
float obterX1Linha(LINHA l);
float obterY1Linha(LINHA l);
float obterX2Linha(LINHA l);
float obterY2Linha(LINHA l);
char* obterCorLinha(LINHA l);

/* ======== MÉTODOS SET ======== */
void definirIDLinha(LINHA l, int id);
void definirX1Linha(LINHA l, float x1);
void definirY1Linha(LINHA l, float y1);
void definirX2Linha(LINHA l, float x2);
void definirY2Linha(LINHA l, float y2);
void definirCorLinha(LINHA l, char* cor);

/* ======== MÉTODOS ADICIONAIS ======== */
float calcularAreaLinha(LINHA l); /**< Retorna 2 vezes o comprimento da linha */

/* ======== DESALOCAÇÃO ======== */
void liberarLinha(LINHA l);

#endif
