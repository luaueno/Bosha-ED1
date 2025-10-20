#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdlib.h>

/**
 * @file circulo.h
 * @brief Módulo para representar círculos.
 *
 * Define uma estrutura opaca para círculos, com coordenadas, raio, cor de borda e preenchimento.
 * Fornece funções para criação, acesso, modificação, cálculo de área e desalocação.
 */

typedef void* CIRCULO; /**< Tipo opaco para círculo */

/* ======== CRIAÇÃO ======== */
CIRCULO novoCirculo(int id, float x, float y, float raio, char* corP, char* corB);

/* ======== MÉTODOS GET ======== */
int obterIDCirculo(CIRCULO c);
float obterXCirculo(CIRCULO c);
float obterYCirculo(CIRCULO c);
float obterRaioCirculo(CIRCULO c);
char* obterCorBCirculo(CIRCULO c);
char* obterCorPCirculo(CIRCULO c);

/* ======== MÉTODOS SET ======== */
void definirIDCirculo(CIRCULO c, int id);
void definirXCirculo(CIRCULO c, float x);
void definirYCirculo(CIRCULO c, float y);
void definirRaioCirculo(CIRCULO c, float raio);
void definirCorBCirculo(CIRCULO c, char* corB);
void definirCorPCirculo(CIRCULO c, char* corP);

/* ======== MÉTODOS ADICIONAIS ======== */
float calcularAreaCirculo(CIRCULO c);

/* ======== DESALOCAÇÃO ======== */
void liberarCirculo(CIRCULO c);

#endif
