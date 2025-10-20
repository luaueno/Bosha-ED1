#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdlib.h>

/**
 * @file retangulo.h
 * @brief Módulo para representar retângulos.
 *
 * Define uma estrutura opaca para retângulos com coordenadas, largura, altura,
 * cor de borda e cor de preenchimento. Fornece funções para criação, acesso,
 * modificação, cálculo de área e desalocação.
 */

typedef void* RETANGULO; /**< Tipo opaco para retângulo */

/* ======== CRIAÇÃO ======== */
RETANGULO novoRetangulo(int id, float x, float y, float largura, float altura, char* corP, char* corB);

/* ======== MÉTODOS GET ======== */
int obterIDRetangulo(RETANGULO r);
float obterXRetangulo(RETANGULO r);
float obterYRetangulo(RETANGULO r);
float obterLarguraRetangulo(RETANGULO r);
float obterAlturaRetangulo(RETANGULO r);
char* obterCorBRetangulo(RETANGULO r);
char* obterCorPRetangulo(RETANGULO r);

/* ======== MÉTODOS SET ======== */
void definirIDRetangulo(RETANGULO r, int id);
void definirXRetangulo(RETANGULO r, float x);
void definirYRetangulo(RETANGULO r, float y);
void definirLarguraRetangulo(RETANGULO r, float largura);
void definirAlturaRetangulo(RETANGULO r, float altura);
void definirCorBRetangulo(RETANGULO r, char* corB);
void definirCorPRetangulo(RETANGULO r, char* corP);

/* ======== MÉTODOS ADICIONAIS ======== */
float calcularAreaRetangulo(RETANGULO r);

/* ======== DESALOCAÇÃO ======== */
void liberarRetangulo(RETANGULO r);

#endif
