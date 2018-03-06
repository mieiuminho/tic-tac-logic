/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "graphics.h"

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
  e.cpos=0;
  for(i=0;i<nl;i++){
    for(j=0;j<nc;j++)
      e.grelha[i][j]=VAZIA;
  }
  return e;
}

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args) {
  if(strlen(args) == 0)
  return inicializar(5,5);
  return str2estado(args);
}

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main() {
ESTADO e = ler_estado(getenv("QUERY_STRING"));
int j, i, sf;
char holder_undo;
getScaleFactor(&sf,e);
COMECAR_HTML;
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    for(i=0;i<e.num_lins;i++){
      for(j=0;j<e.num_cols;j++){
        if (e.grelha[i][j]>FIXO_O)
        {
          e.hist[e.cpos].x=i;
          e.hist[e.cpos].y=j;
          e.cpos++;
          drawPeca(i,j,e,sf);
          e.cpos--;
        }
        else drawPeca(i,j,e,sf);
      }
    }

    abrirLink(e);
    IMAGEM(0, i/2, 80, "novo.png");
    FECHAR_LINK;
    holder_undo = e.grelha[e.hist[e.cpos].x][e.hist[e.cpos].y];
    if (e.cpos)
    {
      e.grelha[e.hist[(e.cpos)-1].x][e.hist[(e.cpos)-1].y] = VAZIA;
      e.cpos--;
      abrirLink(e);
      IMAGEM(0, i/4, 80, "novo.png");
      e.grelha[e.hist[e.cpos].x][e.hist[e.cpos].y] = holder_undo;
      e.cpos++;
      FECHAR_LINK;
    }
    else IMAGEM(0, i/4, 80, "novo.png");

   FECHAR_SVG;
FECHAR_HTML;

    return 0;
  }
