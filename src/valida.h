#ifndef ___VALIDA_H___
#define ___VALIDA_H___
#include "estado.h"

/**
\brief Função que verifica se uma determinada posição se encontra no tabuleiro,
devolvendo "1" caso afirmativo e "0" caso contrário.
@param *e Apontador para o estado
@param i Coordenada correspondente ao eixo dos xx
@param j Coordenada correspondente ao eixo dos yy
*/
int isOnTab (ESTADO * e,int i,int j);

/**
\brief Função que verifica se uma determinada peça numa determinada posição
do tabuleiro é válida. Se a peça em questão for vazia, a função devolve "1"
caso seja válida e "0" caso contrário. Caso a peça em questão não seja vazia,
a função devolve "1" se só for válida uma peça nessa posição e "2" caso nem
um "X" nem um "O" seja válido nessa posição.
@returns O inteiro correspondente a um dos casos acima descritos.
*/
int validaPeca (ESTADO * e,int i,int j);

/**
\brief Função que verifica se duas peças têm o mesmo significado.
@param *e Apontador para o estado
@param i Coordenada correspondente ao eixo dos xx da 1ª peça
@param j Coordenada correspondente ao eixo dos yy da 1ª peça
@param x Coordenada correspondente ao eixo dos xx da 2ª peça
@param y Coordenada correspondente ao eixo dos yy da 2ª peça
@returns "1" caso afirmativo e "0" caso contrário.
*/
int isEqual (ESTADO * e,int i,int j,int x,int y);

/**
\brief Função que altera o parâmetro "e->validade" do "ESTADO" conforme a situação
em que o jogo se encontra. Noutras palavras, caso seja possível completar o
tabuleiro o parâmetro referido toma o valor de IMPOSSIVEL, caso o tabuleiro possua
algum erro o parametro toma o valor de INVALIDO, caso seja possível completar o
tabuleiro o parâmetro toma o valor de VALIDO.
@param Apontador para o estado
*/
void setSemaforo (ESTADO * e);

int isFinished (ESTADO *e);

#endif
