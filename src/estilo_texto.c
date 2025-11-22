#include "estilo_texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura interna (privada no .c) */
typedef struct {
    char* ff;   // font family
    char* fw;   // font weight
    int fs;     // font size
} EstiloTextoInterno;

/**
 * @brief Cria um novo EstiloTexto.
 */
ESTILOTEXTO criaEstiloTexto(char* ff, char* fw, int fs) {

    if (!ff || !fw) 
        return NULL;

    EstiloTextoInterno *et = malloc(sizeof(EstiloTextoInterno));
    if(!et) return NULL;

    et->ff = malloc(strlen(ff) + 1);
    if(!et->ff){
        free(et);
        return NULL;
    }
    strcpy(et->ff, ff);

    et->fw = malloc(strlen(fw) + 1);
    if(!et->fw){
        free(et->ff);
        free(et);
        return NULL;
    }
    strcpy(et->fw, fw);

    et->fs = fs;
    return (ESTILOTEXTO) et;
}

/**
 * @brief Libera toda a memória de EstiloTexto.
 */
void desalocaEstiloTexto(ESTILOTEXTO estilo) {

    if(!estilo) return;

    EstiloTextoInterno *et = (EstiloTextoInterno*) estilo;

    free(et->ff);
    free(et->fw);
    free(et);
}

/**
 * @brief Retorna a font family.
 */
char* getFFEstiloTexto(ESTILOTEXTO estilo) {
    if(!estilo) return NULL;
    return ((EstiloTextoInterno*)estilo)->ff;
}

/**
 * @brief Retorna a font weight.
 */
char* getFWEstiloTexto(ESTILOTEXTO estilo) {
    if(!estilo) return NULL;
    return ((EstiloTextoInterno*)estilo)->fw;
}

/**
 * @brief Retorna o font size.
 */
int getFSEstiloTexto(ESTILOTEXTO estilo) {
    if(!estilo) return 0;
    return ((EstiloTextoInterno*)estilo)->fs;
}
