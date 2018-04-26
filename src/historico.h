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

#endif