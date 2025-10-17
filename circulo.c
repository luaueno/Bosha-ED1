#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdlib.h>
#include "formas.h"  // Para usar TipoForma

typedef void* CIRCULO;

/**
 * @brief Cria e inicializa um novo círculo.
 * 
 * @param id Identificador do círculo.
 * @param x Coordenada X do centro.
 * @param y Coordenada Y do centro.
 * @param raio Raio do círculo.
 * @param corP Cor de preenchimento.
 * @param corB Cor da borda.
 * @return Ponteiro para o círculo criado.
 */
CIRCULO criaCirculo(int id, float x, float y, float raio, char* corP, char* corB);

// Getters
int getIDCirculo(CIRCULO c);
float getXCirculo(CIRCULO c);
float getYCirculo(CIRCULO c);
float getRaioCirculo(CIRCULO c);
char* getCorBCirculo(CIRCULO c);
char* getCorPCirculo(CIRCULO c);
TipoForma getTipoCirculo(CIRCULO c); // Novo

// Setters
void setIDCirculo(CIRCULO c, int id);
void setXCirculo(CIRCULO c, float x);
void setYCirculo(CIRCULO c, float y);
void setRaioCirculo(CIRCULO c, float raio);
void setCorBCirculo(CIRCULO c, char* corB);
void setCorPCirculo(CIRCULO c, char* corP);

// Funções auxiliares
float calculoAreaCirculo(CIRCULO c);
void desalocaCirculo(CIRCULO c);

#endif
