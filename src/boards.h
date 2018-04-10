#ifndef ___BOARDS_H___
#define ___BOARDS_H___
#include "estado.h"

/**
@file boards.h
Criação das funções que desenham tabuleiros
*/

#define MAX_PATH 100

void fazTab(ESTADO *e);

/**
Define um novo estado através de um ficheiro
@returns O estado
*/
ESTADO le_tabuleiro();


#endif