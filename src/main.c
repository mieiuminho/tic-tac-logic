/**
@file exemplo.c
Esqueleto do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "valida.h"

#define GRELHA  4
#define TAM 40

#define TAB_PATH "/var/www/html/tabuleiros/"
#define MAX_PATH 100

/**
Função que inicializa o estado

Esta função está vazia

@returns Um novo estado
*/
ESTADO inicializar(int nl, int nc) {
  ESTADO e;
  int i,j;
  e.num_lins=nl;
  e.num_cols=nc;
  e.spU=e.spR=e.epR=e.epU=0;
  for(i=0;i<nl;i++){
    for(j=0;j<nc;j++)
      e.grelha[i][j]=VAZIA;
  }
  e.grelha [1][2] = BLOQUEADA;
  e.grelha [3][4] = FIXO_O;
  e.grelha [2][3] = FIXO_X;
  return e;
}

ESTADO le_tabuleiro()
{
  ESTADO e;
  int nl, nc;
  int i,j;
  char linha[20];
  char nomef[MAX_PATH];

  sprintf(nomef, "%s%s", TAB_PATH, "tabuleiro1.txt");
  FILE *fp=fopen(nomef, "r");
  fscanf(fp, "%d %d", &nl, &nc); // possivel erro

  e.num_lins = nl;
  e.num_cols = nc;
  e.spU=e.spR=e.epR=e.epU=e.spA=e.epA=0;
  for(i=0;i<nl;i++){
    fscanf(fp, "%s", linha);
    for(j=0;j<nc;j++)
      switch (linha[j]) {
        case 'X':
        case 'x': e.grelha[j][i] = FIXO_X;break;
        case 'O':
        case 'o': e.grelha[j][i] = FIXO_O;break;
        case '#': e.grelha[j][i] = BLOQUEADA;break;
        default : e.grelha[j][i] = VAZIA;
      }
  }
  return e;
}

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args)
{
  if(strlen(args) == 0)
    return le_tabuleiro();
  return str2estado(args);
}

void fazTab (ESTADO * e)
{
  int jog;
  int i,j,sf;
  getScaleFactor(&sf,(*e));
  for(i=0;i<(*e).num_lins;i++)
  {
    for(j=0;j<(*e).num_cols;j++)
    {
      if ((*e).grelha[i][j]>FIXO_O)
      {
        jog=fromPair(i,j);
        push(e,jog,0);
        drawPeca(i,j,(*e),sf,validaPeca(e,i,j));
        pop(e,0);
        printf("%d\n",e->spU);
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
      fazAncoras(&e);
    FECHAR_SVG;
  FECHAR_HTML;

    return 0;
}
