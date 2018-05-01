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
\brief Função que coloca em level a diretória dos tabuleiros correspondentes ao nível de dificuldade.
@param *e Apontador para o estado.
@param *level String onde será escrita a diretoria.
*/
void boardLevelPath (ESTADO * e, char * level);

/**
\brief Função que lê o tabuleiro do ficheiro.
@param *e Apontador para o ESTADO.
@param x Número identificador do tabuleiro.
@returns O estado
*/
ESTADO le_tabuleiro(ESTADO *e, int x);


#endif
