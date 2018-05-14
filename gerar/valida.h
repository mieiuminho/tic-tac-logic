#ifndef ___VALIDA_H___
#define ___VALIDA_H___
#include "puzzle.h"

/**
\brief Função que verifica se uma determinada posição se encontra no tabuleiro,
devolvendo "1" caso afirmativo e "0" caso contrário.
@param *e Apontador para o estado
@param i Coordenada correspondente ao eixo dos xx
@param j Coordenada correspondente ao eixo dos yy
*/
int isOnTab (PUZZLE *board, int i, int j);

/**
\brief Função que verifica se uma determinada peça numa determinada posição
do tabuleiro é válida. Se a peça em questão for vazia, a função devolve "1"
caso seja válida e "0" caso contrário. Caso a peça em questão não seja vazia,
a função devolve "1" se só for válida uma peça nessa posição e "2" caso nem
um "X" nem um "O" seja válido nessa posição.
@returns O inteiro correspondente a um dos casos acima descritos.
*/
int validaPeca (PUZZLE *board, int i, int j);

/**
\brief Função que verifica se duas peças têm o mesmo significado.
@param *e Apontador para o estado
@param i Coordenada correspondente ao eixo dos xx da 1ª peça
@param j Coordenada correspondente ao eixo dos yy da 1ª peça
@param x Coordenada correspondente ao eixo dos xx da 2ª peça
@param y Coordenada correspondente ao eixo dos yy da 2ª peça
@returns "1" caso afirmativo e "0" caso contrário.
*/
int isEqual (PUZZLE *board, int i, int j, int x, int y);

int isFull (PUZZLE *board);

int validade (PUZZLE *board);

#endif
