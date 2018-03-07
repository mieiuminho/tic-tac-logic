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

#define GRELHA  4
#define TAM 40
#define GET_SEGUINTE(JOG,I,J,E) JOG.peca = (E.grelha[I][J]==5) ? 3 : ((E.grelha[I][J])+1)

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
  e.compHist=0;
  for(i=0;i<nl;i++){
    for(j=0;j<nc;j++)
      e.grelha[i][j]=VAZIA;
  }
  e.grelha [1][2] = BLOQUEADA;
  e.grelha [3][4] = FIXO_O;
  e.grelha [2][3] = FIXO_X;
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

void fazTab (ESTADO * e)
{
  JOGADA jog;
  int i,j,sf;
  getScaleFactor(&sf,(*e));
  for(i=0;i<(*e).num_lins;i++){
      for(j=0;j<(*e).num_cols;j++){
        if ((*e).grelha[i][j]>FIXO_O)
        {
          GET_SEGUINTE(jog,i,j,(*e));
          adicionaHistorico(e,jog);
          drawPeca(i,j,(*e),sf);
          retiraHistorico(e);
        }
        else drawPeca(i,j,(*e),sf);
      }
    }
}
/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main() {
ESTADO e = ler_estado(getenv("QUERY_STRING"));
COMECAR_HTML;
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    fazTab(&e);
    abrirLink(inicializar(e.num_lins,e.num_cols));
      IMAGEM(0, 4, 80, "novo.png");
    FECHAR_LINK;
    fazUndo(&e);
    fazRedo(&e);
  FECHAR_SVG;
FECHAR_HTML;

    return 0;
  }
