#ifndef ___SOLVER_H___
#define ___SOLVER_H___
#include "estado.h"

/**
@file solver.h
Definição de funções que alteram o "ESTADO", preenchendo-o com os casos mais
imediatos, ou seja, quando duas peças iguais estão separadas por um espaço, ou quando
duas peças iguais se encontram em posições consecutivas em qualquer uma das posições
ortogonais. Estão também já aqui definidos os casos em que é preciso recorer ao método
de "suposição" para resolver um determinado tabuleiro.
*/


/**
\brief Função que preenche os casos imediatos descritos acima.
@param *e Apontador para o estado
@param *x Apontador para a coordenada x da posição preenchida por fillIn.
@param *y Apontador para a coordenada y da posição preenchida por fillIn.
@returns "0" caso só seja possível fornecer uma ajuda com recurso à "suposição", "1" caso
seja possível colocar uma dar uma ajuda e, por último, "2" caso não seja possível fornecer
uma ajuda.
*/
int fillIn (ESTADO *e, int *x, int *y);

/**
\brief Função que percorre o tabuleiro à procura de peças que necessitem de estar numa
determinada posição do tabuleiro, pois de outra forma o tabuleiro não teria uma solução
válida, para isso utiliza a capacidade de marcar ancoras, ou seja, "joga" uma determinada
peça numa posição e depois preenche o jogo normalmente. Se chegar a uma imcopatibilidade
então já sabe qual a peça a colocar nessa posição e por isso volta para ancora anteriormente
feita e coloca a peça na posição correspondente, caso não encontre nenhum problema volta para
a ancora e faz o mesmo para a peça seguinte.
@param *e Apontador para o estado
*/
void findImpossible (ESTADO *e);

/**
\brief Função que percorre o tabuleiro e troca o GIF que indica que uma determinada peça
se encontra no tabuleiro através do uso de um "HINT" pela peça correspondente.
@param *e Apontador para o estado
*/
void remHints (ESTADO *e);

/**
\brief Função que preenche o tabuleiro completamente utilizando as funções fillIn e
findImpossible.
@param *e Apontador para o estado
*/
void completaTabuleiro (ESTADO * e);

#endif
