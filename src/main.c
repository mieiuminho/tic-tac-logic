/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "valida.h"

#define GRELHA  4
#define TAM 40

/**
Função que inicializa o estado

Esta função está vazia

@returns Um novo estado
*/
ESTADO inicializar(int nl, int nc) {
  ESTADO e ;
  int i,j;
  e.num_lins=nl;
  e.num_cols=nc;
  e.compHistU=0;
  e.compHistR=0;
  for(i=0;i<nl;i++){
    for(j=0;j<nc;j++)
      e.grelha[i][j]=VAZIA;
  }
  e.grelha [1][2] = BLOQUEADA;
  e.grelha [3][4] = FIXO_O;
  e.grelha [2][3] = FIXO_X;
  return e;
}

void igualaJog (JOGADA * jog,int i,int j,ESTADO e)
{
  (*jog).x = i;
  (*jog).y = j;
  (*jog).peca = ((e.grelha[i][j]==5) ? 3 : ((e.grelha[i][j])+1));
}
//C
/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args)
{
  if(strlen(args) == 0)
  return inicializar(8,8);
  return str2estado(args);
}


void fazTab (ESTADO * e)
{
  JOGADA jog;
  int i,j,sf;
  getScaleFactor(&sf,(*e));
  for(i=0;i<(*e).num_lins;i++)
  {
    for(j=0;j<(*e).num_cols;j++)
    {
      if ((*e).grelha[i][j]>FIXO_O)
      {
        igualaJog (&jog,i,j,(*e));
        adicionaHistorico(e,jog,0);
        drawPeca(i,j,(*e),sf,validaPeca(e,i,j));
        retiraHistorico(e,0);
      }
      else drawPeca(i,j,(*e),sf,validaPeca(e,i,j));
    }
  }
}

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main()
{
  ESTADO e = ler_estado(getenv("QUERY_STRING"));

  COMECAR_HTML;
    ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
      IMAGEM_ABS(752, 0, 400, 200, "title.png");
      fazTab(&e);

      abrirLink(inicializar(e.num_lins,e.num_cols));
        IMAGEM_ABS(852, 800, 200, 100, "start.png");
      FECHAR_LINK;

      fazUndo(&e);
      fazRedo(&e);
    FECHAR_SVG;
  FECHAR_HTML;

    return 0;
}
