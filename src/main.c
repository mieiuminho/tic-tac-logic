/**
@file main.c
Esqueleto do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "menu.h"
#include "solver.h"
#include "valida.h"

#define GRELHA  4
#define TAM     40

/**
\brief Função que processa as ordens recebidas pelo jogo.
@param *e Apontador para o ESTADO.
@param *ordem String corresponde à ordem recebida.
*/
void processa(ESTADO * e,char * ordem)
{
    int x,y,a;
    remHints(e);
    switch(ordem[0])
    {
        case 'x': sscanf(ordem,"x-%d-y-%d",&x,&y);
                  if (e->grelha[x][y]==SOL_O) e->grelha[x][y]=VAZIA; else e->grelha[x][y]++;
                  push(x,y,e->numAncs,&(e->undo));
                  e->sizeU++;
                  break;
        case 'a': marcaAncora(e);break;
        case 'v': voltaAncora(e);break;
        case 'u': pop(&x,&y,&a,&(e->undo));
                  switch(e->grelha[x][y])
                  {
                    case HINT_X:
                    case HINT_O:
                    case SOL_X:e->grelha[x][y]=VAZIA;break;
                    case SOL_O:e->grelha[x][y]=SOL_X;break;
                    case VAZIA:e->grelha[x][y]=SOL_O;break;
                 } 
                  if (a<e->numAncs) e->numAncs--;
                  push(x,y,a,&(e->redo));
                  e->sizeR++;
                  e->sizeU--;break;
        case 'r': pop(&x,&y,&a,&(e->redo));
                  if (e->grelha[x][y]==SOL_O) e->grelha[x][y]=VAZIA; else e->grelha[x][y]++;
                  if (a>e->numAncs) e->numAncs++;
                  push(x,y,a,&(e->undo));
                  e->sizeR--;
                  e->sizeU++;break;
        case 'i': sscanf(ordem,"id-%d",&x);
                  e->id = x;
                  break;
        case 't': sscanf(ordem,"tab%d",&x);
                  (*e)=le_tabuleiro(e,x);
                  e->id=JOGO;
                  break;
        case 'c': colorscheme(e);
                  break;
        case 'h': if (fillIn(e,&x,&y)==0) findImpossible(e);
                  break;
    }
}


/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/

/*
ESTADO ler_estado(char *args)
{
  ESTADO e;

  if(strlen(args) == 0) e.id = INICIO;
  else if (strcmp(args,"puzzles") == 0) e.id = SELECAO;
  else if (strcmp(args,"puzzles/1") == 0){
    e = le_tabuleiro("tabuleiro1.txt");
    e.id = JOGO;
  } else if (strcmp(args,"puzzles/2") == 0) {
    e = le_tabuleiro("tabuleiro2.txt");
    e.id = JOGO;
  } else if (strcmp(args,"puzzles/3") == 0) {
    e = le_tabuleiro("tabuleiro3.txt");
    e.id = JOGO;
  } else {
      e = str2estado(args);
      e.id = JOGO;
  }
  return e;
}
*/

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main()
{
  ESTADO e;
  char user [20];
  char action [20];
  getUserAndAction(getenv("QUERY_STRING"),user,action);
  readFile(user,&e);
  processa(&e,action);
  writeFile(user,e);

  COMECAR_HTML;

  switch (e.id) {
    case INICIO: drawMenu(&e,user); break;
    case SELECAO: drawSelecao(&e,user); break;
    case JOGO: drawJogo(&e,user); break;
  }

  FECHAR_HTML;

  return 0;
}
