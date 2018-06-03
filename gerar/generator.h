#ifndef ___GENERATOR_H___
#define ___GENERATOR_H___
#include "puzzle.h"

/**
\brief Função que gera tabuleiros.
@param *board Apontador para o tabuleiro.
@param dif Identificador da dificuldade.
*/
void geraTabuleiro (PUZZLE *board, int dif);

/**
\brief Função que gera o tabuleiro de dificuldade "fácil".
@param *board Apontador para o tabuleiro.
*/
void geraEasy (PUZZLE *board);

/**
\brief Função que gera o tabuleiro de dificuldade "difícil".
@param *board Apontador para o tabuleiro.
*/
void geraHard (PUZZLE * board);

#endif