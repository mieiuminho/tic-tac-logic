#ifndef ___BOARDS_H___
#define ___BOARDS_H___
#include "estado.h"

/**
@file boards.h
Criação das funções que desenham tabuleiros
*/

#define MAX_PATH 100

/**
\brief Função que desenha o tabuleiro.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void fazTab(ESTADO *e,char * user);

/**
\brief Função que lê o tabuleiro do ficheiro.
@param *e Apontador para o ESTADO.
@param x Número identificador do tabuleiro.
@returns O estado
*/
ESTADO le_tabuleiro(ESTADO *e, int x);


#endif