/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"

#define MAX_BUFFER  10240
#define GRELHA  4
#define TAM 40
#define ECRA_X 1904
#define ECRA_Y 938
#define DTAB 800
#define MUDA_SEGUINTE(I,J,E) E.grelha[I][J] = (E.grelha[I][J]==5) ? 3 : ((E.grelha[I][J])+1)

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
  for(i=0;i<nl;i++){
    for(j=0;j<nc;j++)
      e.grelha[i][j]=VAZIA;
  }
  return e;
}

void getScaleFactor(int * sf, ESTADO e)
{
  *sf= (e.num_lins >= e.num_cols) ? (float) (DTAB/e.num_lins) : (float) (DTAB/e.num_cols);
}

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args) {
  if(strlen(args) == 0)
  return inicializar(12,12);
  return str2estado(args);
}

/**
Coloca a imagem correspondente no local indicado
@param A posição x e y onde a imagem vai ser colocada assim como um char para identificar qual será essa imagem
*/
void drawPeca (int i,int j,char x,ESTADO e,int sf)
{
  int cx = ((ECRA_X-DTAB)/2)-1,cy = ((ECRA_Y-DTAB)/2)-1,fnrx,fnry;//fnr = fix non rect
  fnrx = (DTAB - (e.num_lins*sf))/2;
  fnry = (DTAB -(e.num_cols*sf))/2;
  char s [50];
  switch (x)
  {
    case VAZIA : strcpy(s,"vazio.png");break;
    case BLOQUEADA : strcpy(s,"bloq.png");break;
    case FIXO_X :
    case SOL_X  : strcpy(s,"X.png");break;
    case FIXO_O :
    case SOL_O : strcpy(s,"O.png");break;
  }
  IMAGEM(i+cx+fnrx,j+cy+fnry,sf,s);
}

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main() {
ESTADO e = ler_estado(getenv("QUERY_STRING"));
int j, i, sf;
char holder;
getScaleFactor(&sf,e);
COMECAR_HTML;
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    for(i=0;i<e.num_lins;i++){
      for(j=0;j<e.num_cols;j++){
        if (e.grelha[i][j]>FIXO_X)
        {
          holder = e.grelha[i][j];
          MUDA_SEGUINTE(i,j,e);
          ABRIR_LINK(estado2str(e));
          drawPeca(i,j,holder,e,sf);
          e.grelha[i][j] = holder;
          FECHAR_LINK;
        }
        else drawPeca(i,j,e.grelha[i][j],e,sf);
      }
    }

    ABRIR_LINK("http://localhost/cgi-bin/GandaGalo?");
    IMAGEM(0, i/2, 80, "novo.png");
    FECHAR_LINK;

   FECHAR_SVG;
FECHAR_HTML;

    return 0;
  }
