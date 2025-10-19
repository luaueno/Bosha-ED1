#ifndef TEXTO_H
#define TEXTO_H

#include <stdlib.h>
#include "formas.h"

typedef void* TEXTO;

TEXTO criaTexto(int id, float x, float y, char* corB, char* corP, char ancora, char* txt);
int getIDTexto(TEXTO t);
float getXTexto(TEXTO t);
float getYTexto(TEXTO t);
char getAncoraTexto(TEXTO t);
char* getCorBTexto(TEXTO t);
char* getCorPTexto(TEXTO t);
char* getTxtTexto(TEXTO t);
TipoForma getTipoTexto(TEXTO t); // Novo
float getComprimentoTexto(TEXTO t);
float getX1Texto(TEXTO t);
float getX2Texto(TEXTO t);
float calculoAreaTexto(TEXTO t);

void setIDTexto(TEXTO t, int id);
void setXTexto(TEXTO t, float x);
void setYTexto(TEXTO t, float y);
void setCorBTexto(TEXTO t, char* corB);
void setCorPTexto(TEXTO t, char* corP);
void setAncoraTexto(TEXTO t, char ancora);
void setTxtTexto(TEXTO t, char* txt);

void desalocaTexto(TEXTO t);

#endif
