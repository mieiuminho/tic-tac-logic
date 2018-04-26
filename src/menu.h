#ifndef ___MENU_H___
#define ___MENU_H___
#include "estado.h"


/**
@file menu.h
Criação das funções que interpretam o meu atual
*/

/**
\brief Função que desenha o menu.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawMenu (ESTADO *e, char *user);

/**
\brief Função que desenha o menu de seleção de puzzles.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawSelecao (ESTADO *e, char *user);

/**
\brief Função que desenha o jogo propriamente dito.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawJogo (ESTADO *e, char *user);

#endif