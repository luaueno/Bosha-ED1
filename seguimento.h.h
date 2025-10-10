#ifndef SEGMENTO_H
#define SEGMENTO_H

/**
 * @file segmento.h
 * @brief Interface para a estrutura que representa um segmento de reta em um plano 2D.
 *
 * Este módulo define um tipo abstrato de dado para representar um segmento em coordenadas planas,
 * seguindo convenções SVG, com funções para criar, acessar, modificar e liberar segmentos.
 */

/// Tipo opaco que representa um segmento
typedef void* SEGMENTO;

/**
 * @brief Cria um novo segmento.
 * 
 * @param id Identificador único do segmento.
 * @param xi Coordenada X do ponto inicial.
 * @param yi Coordenada Y do ponto inicial.
 * @param xf Coordenada X do ponto final.
 * @param yf Coordenada Y do ponto final.
 * @param cor Cor do segmento (string).
 * @return Um ponteiro para o segmento criado (tipo SEGMENTO).
 */
SEGMENTO criaSegmento(int id, float xi, float yi, float xf, float yf, char* cor);

/**
 * @brief Retorna o identificador do segmento.
 * 
 * @param s Ponteiro para o segmento.
 * @return O identificador do segmento.
 */
int getIDSegmento(SEGMENTO s);

/**
 * @brief Retorna a coordenada X do ponto inicial.
 * 
 * @param s Ponteiro para o segmento.
 * @return A coordenada X do ponto inicial.
 */
float getXiSegmento(SEGMENTO s);

/**
 * @brief Retorna a coordenada Y do ponto inicial.
 * 
 * @param s Ponteiro para o segmento.
 * @return A coordenada Y do ponto inicial.
 */
float getYiSegmento(SEGMENTO s);

/**
 * @brief Retorna a coordenada X do ponto final.
 * 
 * @param s Ponteiro para o segmento.
 * @return A coordenada X do ponto final.
 */
float getXfSegmento(SEGMENTO s);

/**
 * @brief Retorna a coordenada Y do ponto final.
 * 
 * @param s Ponteiro para o segmento.
 * @return A coordenada Y do ponto final.
 */
float getYfSegmento(SEGMENTO s);

/**
 * @brief Retorna a cor do segmento.
 * 
 * @param s Ponteiro para o segmento.
 * @return Ponteiro para a string que representa a cor.
 */
char* getCorSegmento(SEGMENTO s);

/**
 * @brief Define o identificador do segmento.
 * 
 * @param s Ponteiro para o segmento.
 * @param id Novo identificador.
 */
void setIDSegmento(SEGMENTO s, int id);

/**
 * @brief Define a coordenada X do ponto inicial.
 * 
 * @param s Ponteiro para o segmento.
 * @param xi Nova coordenada X inicial.
 */
void setXiSegmento(SEGMENTO s, float xi);

/**
 * @brief Define a coordenada Y do ponto inicial.
 * 
 * @param s Ponteiro para o segmento.
 * @param yi Nova coordenada Y inicial.
 */
void setYiSegmento(SEGMENTO s, float yi);

/**
 * @brief Define a coordenada X do ponto final.
 * 
 * @param s Ponteiro para o segmento.
 * @param xf Nova coordenada X final.
 */
void setXfSegmento(SEGMENTO s, float xf);

/**
 * @brief Define a coordenada Y do ponto final.
 * 
 * @param s Ponteiro para o segmento.
 * @param yf Nova coordenada Y final.
 */
void setYfSegmento(SEGMENTO s, float yf);

/**
 * @brief Define a cor do segmento.
 * 
 * @param s Ponteiro para o segmento.
 * @param cor Nova cor (string).
 */
void setCorSegmento(SEGMENTO s, char* cor);

/**
 * @brief Calcula uma métrica associada ao segmento.
 *
 * Nesta implementação, define-se a “métrica” do segmento como sendo
 * duas vezes o seu comprimento, de acordo com:
 *
 *     métrica = 2 * sqrt((xf - xi)² + (yf - yi)²)
 *
 * Esse valor é útil para comparações com outras formas geométricas.
 *
 * @param s Ponteiro para o segmento.
 * @return Valor da métrica calculada.
 */
float calculaMetricaSegmento(SEGMENTO s);

/**
 * @brief Libera a memória alocada para o segmento.
 * 
 * @param s Ponteiro para o segmento.
 */
void liberaSegmento(SEGMENTO s);

#endif
