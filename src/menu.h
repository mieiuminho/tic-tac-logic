#ifndef ___MENU_H___
#define ___MENU_H___
#include "estado.h"

/**
@file menu.h
Criação das funções que interpretam como desenhar o menu atual
*/

/**
\brief Função que desenha o menu inicial.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawStart (ESTADO *e, char *user);

/**
\brief Função que desenha o menu para a escolha do nível de dificuldade.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawLobby (ESTADO *e, char *user);

/**
\brief Função que desenha o menu de seleção de puzzles de um determinado nível.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawLevel (ESTADO *e, char *user);

/**
\brief Função que desenha o jogo propriamente dito.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void drawGame (ESTADO *e, char *user);

#endif
