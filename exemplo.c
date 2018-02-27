/**
@file exemplo.c
Esqueleto do programa
*/

#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"

#define MAX_BUFFER		10240
#define GRELHA			4
#define TAM			40

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
ESTADO e= ler_estado(getenv("QUERY_STRING"));
int j, i;

COMECAR_HTML;
  ABRIR_SVG(600, 600);
    for(i=0;i<e.num_lins;i++){
      for(j=0;j<e.num_cols;j++){
        switch(e.grelha[i][j]){
          case VAZIA : e.grelha[i][j]=SOL_X;
                       FECHAR_LINK;
                       ABRIR_LINK(estado2str(e));
                        IMAGEM(i,j,40, "vazio.png"); break;
          case BLOQUEADA: IMAGEM(i,j,40, "bloq.png"); break;
          case FIXO_X: IMAGEM(i,j,40, "X.png"); break;
          case SOL_X: IMAGEM(i,j,40, "X.png"); break;
          case FIXO_O: IMAGEM(i,j,40, "O.png"); break;
          case SOL_O: IMAGEM(i,j,40, "O.png"); break;
        }
      }
    }

    ABRIR_LINK("http://localhost/cgi-bin/GandaGalo");
    IMAGEM(0, i/2, 80, "novo.png");
    FECHAR_LINK;

   FECHAR_SVG;
FECHAR_HTML;

    return 0;
  }
