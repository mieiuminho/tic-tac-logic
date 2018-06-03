#ifndef ___HISTORICO_H___
#define ___HISTORICO_H___
#include "estado.h"

/**
@file historico.h
Criação das funções responsaveis pela manipulação do histórico
*/

/**
\brief Função que percorre a stack do undo e volta "atrás" para a peça
correspondente até que o número de ancora dessa jogada seja inferior ao
número de ancora onde o jogo está atualmente. Fazendo por fim a diminuição
do número de ancora atual do estado.
@param e Apontador para o estado.
*/
void voltaAncora(ESTADO *e);

/**
\brief Função que aumenta o número da ancora onde o jogo
se encontra num determinado momento.
@param e Apontador para o estado.
*/
void marcaAncora(ESTADO *e);

/**
\brief Função que realiza o processo de Undo do Jogo,
adicionando uma certa jogada a uma lista ligada para o Redo
e retirando da lista ligada do Undo.
@param e Apontador para o estado.
@param x Apontador para a coordenada do eixo xx da jogada.
@param y Apontador para a coordenada do eixo yy da jogada.
@param a Apontador para o numero da ancora
*/
void fazUndo(ESTADO *e , int *x, int *y, int *a);

/**
\brief Função que realiza o processo de Redo do Jogo,
adicionando uma certa jogada a uma lista ligada para o Undo
e retirando da lista ligada do Redo.
@param e Apontador para o estado.
@param x Apontador para a coordenada do eixo xx da jogada.
@param y Apontador para a coordenada do eixo yy da jogada.
@param a Apontador para o numero da ancora
*/
void fazRedo(ESTADO *e, int *x, int *y, int *a);

#endif
