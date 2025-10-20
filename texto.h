#ifndef TEXTO_H
#define TEXTO_H

#include <stdlib.h>

/**
 * @file texto.h
 * @brief Módulo para representar textos em um plano 2D.
 *
 * Define uma estrutura opaca para textos com posição, âncora,
 * cor de preenchimento e borda, ID e conteúdo textual.
 * Fornece funções para criação, acesso, modificação,
 * cálculo de "área" aproximada e desalocação.
 */

typedef void* TEXTO; /**< Tipo opaco para texto */

/* ======== CRIAÇÃO ======== */
TEXTO novoTexto(int id, float x, float y, char* corB, char* corP, char ancora, char* txt);

/* ======== MÉTODOS GET ======== */
int obterIDTexto(TEXTO t);
float obterXTexto(TEXTO t);
float obterYTexto(TEXTO t);
char obterAncoraTexto(TEXTO t);
char* obterCorBTexto(TEXTO t);
char* obterCorPTexto(TEXTO t);
char* obterConteudoTexto(TEXTO t);

/* Comprimento e limites */
float obterComprimentoTexto(TEXTO t);
float obterX1Texto(TEXTO t);
float obterX2Texto(TEXTO t);

/* ======== MÉTODOS SET ======== */
void definirIDTexto(TEXTO t, int id);
void definirXTexto(TEXTO t, float x);
void definirYTexto(TEXTO t, float y);
void definirCorBTexto(TEXTO t, char* corB);
void definirCorPTexto(TEXTO t, char* corP);
void definirAncoraTexto(TEXTO t, char ancora);
void definirConteudoTexto(TEXTO t, char* txt);

/* ======== MÉTODOS ADICIONAIS ======== */
float calcularAreaTexto(TEXTO t); /**< Retorna área aproximada do texto */

/* ======== DESALOCAÇÃO ======== */
void liberarTexto(TEXTO t);

#endif
