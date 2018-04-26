#ifndef ___GRAPHICS_H___
#define ___GRAPHICS_H___
#include "estado.h"
#define ECRA_X 1904
#define ECRA_Y 938
#define DTAB 600
#define MUDA_SEGUINTE(I,J,E) E->grelha[I][J] = (E->grelha[I][J]==5) ? 3 : ((E->grelha[I][J])+1)
#define MAX_BUFFER  10240

/**
\brief Função que abre o link
@param *l Link
*/
void abrirLinkABS(char * l);

/**
\brief Função que indica o próximo estado.
@param *e Apontador para o estado.
*/
void colorscheme (ESTADO * e);

/**
\brief Função que coloca em path a diretória das imagens correspondentes ao tema.
@param *e Apontador para o estado.
@param *path String onde será escrita a diretoria.
*/
void colorSchemePath (ESTADO * e, char * path);

/**
\brief Função que coloca em *sf o fator de escala necessário para desenhar todos os
elementos.
@param *sf Apontador para o inteiro onde vai ser guardado o fator de escala.
@param *e Apontador para o estado.
*/
void getScaleFactor(int * sf, ESTADO * e);

/**
\brief Função que calcula o deslocamento necessário para que as peças fiquem
centradas no ecrã, ou seja, calcula o local onde vai ser desenhada a peça
do canto superior esquerdo tabuleiro para que mais tarde seja mais fácil
tratar dos deslocamentos de cada uma das peças.
@param *e Apontador para o estado.
@param sf Inteiro onde está o fator de escala.
@param *fx Apontador para o inteiro onde ficará guardada a posição x (em valor absoluto) da peça do canto superior esquerdo.
@param *fy Apontador para o inteiro onde ficará guardada a posição y (em valor absoluto) da peça do canto superior esquerdo.
*/
void calculaCentroPeca (ESTADO * e,int sf,int * fx,int * fy);

/**
\brief Função que desenha uma peça jogável no tabuleiro, ou seja, ou peça com 
a instrução para mudar para o estado "seguinte".
@param *e Apontador para o estado.
@param i Inteiro com o valor do deslocamento relativo em x.
@param j Inteiro com o valor do deslocamento relativo em y.
@param sf Inteiro onde está o fator de escala.
@param *s string com o nome da imagem da respetiva peça a desenhar.
@param *user string com o nome do utilizador que está a jogar.
*/
void butaoProxEstadoJog (ESTADO * e,int i,int j,int sf,char * s,char * user);

/**
\brief Função que desenha uma peça bloqueada do tabuleiro.
@param *e Apontador para o estado.
@param i Inteiro com o valor do deslocamento relativo em x.
@param j Inteiro com o valor do deslocamento relativo em y.
@param sf Inteiro onde está o fator de escala.
@param *s string com o nome da imagem da respetiva peça a desenhar.
*/ 
void drawBloq (ESTADO * e,int i,int j,int sf,char * s);

/**
\brief Função que desenha cada peça.
@param i Coordenada correspondente ao eixo dos xx da posição da peça.
@param j Coordenada correspondente ao eixo dos yy da posição da peça.
@param *e Apontador para o estado.
@param sf Scale Factor.
@param vPeca Resultado de "validaPeca".
@param *user Nome do usuário.
*/
void drawPeca (int i,int j,ESTADO * e,int sf,int vPeca,char * user);

/**
\brief Função que desenha cada butão.
@param *e Apontador para o estado.
@param x Coordenada da imagem segundo o eixo dos xx.
@param y Coordenada da imagem segundo o eixo dos yy.
@param sx Fator de escala segundo o eixo dos xx.
@param sy Fator de escala segundo o eixo dos yy.
@param *s Nome do ficheiro da imagem.
@param *action Ação realizada pelo butão.
@param *user Nome do usuário.
*/
void drawButton(ESTADO * e, int x, int y, int sx, int sy , char * s,char * action, char * user);

/**
\brief Função que verifica se um tabuleiro a determinada altura está "VALIDO", ou seja, 
suscetível de ser completado, "INVALIDO", ou seja, com algum erro, ou ainda, "IMPOSSIVEL",
que é quando ainda não existe nenhuma violação explícita das regras do jogo, mas existe 
uma situação imcompatível (significa que o tabuleiro não pode ser completado respeitando 
as regras do jogo.)
@param *e Apontador para o estado.
*/
void drawSemaforo(ESTADO * e);

#endif
