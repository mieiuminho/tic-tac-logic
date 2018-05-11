#ifndef ___HISTORICO_H___
#define ___HISTORICO_H___
#include "estado.h"

/**
\brief Função que percorre a stack do undo e volta "atrás" para a peça
correspondente até que o número de ancora dessa jogada seja inferior ao
número de ancora onde o jogo está atualmente. Fazendo por fim a diminuição
do número de ancora atual do estado.
@param *e Apontador para o estado.
*/

void voltaAncora(ESTADO *);

/**
\brief Função que aumenta o número da ancora onde o jogo
se encontra num determinado momento.
@param *e Apontador para o estado.
*/
void marcaAncora(ESTADO *);


/**
\brief Função que realiza o processo de Undo do Jogo,
adicionando uma certa jogada a uma lista ligada para o Redo
e retirando da lista ligada do Undo.
@param *e Apontador para o estado.
@param *x Apontador para a coordenada do eixo xx da jogada.
@param *y Apontador para a coordenada do eixo yy da jogada.
@param *anc Apontador para o número de ancora da jogada.
*/
void fazUndo(ESTADO *,int *,int *,int *);

/**
\brief Função que realiza o processo de Redo do Jogo,
adicionando uma certa jogada a uma lista ligada para o Undo
e retirando da lista ligada do Redo.
@param *e Apontador para o estado.
@param *x Apontador para a coordenada do eixo xx da jogada.
@param *y Apontador para a coordenada do eixo yy da jogada.
@param *anc Apontador para o número de ancora da jogada.
*/
void fazRedo(ESTADO *,int *,int *,int *);

#endif
