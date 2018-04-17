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
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função inicializar
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
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

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main()
{
  ESTADO e = ler_estado(getenv("QUERY_STRING"));

  COMECAR_HTML;

  switch (e.id) {
    case INICIO: drawMenu(); break;
    case SELECAO: drawSelecao(&e); break;
    case JOGO: drawJogo(&e); break;
  }

  FECHAR_HTML;

  return 0;
}
