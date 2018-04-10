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
#include "valida.h"

#define GRELHA  4
#define TAM 40


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

/**
Função principal do programa
@returns 0 se tudo correr bem
*/
int main()
{
  ESTADO e = ler_estado(getenv("QUERY_STRING"));

  if (strlen(getenv("QUERY_STRING"))==0) e.id = INICIO;
  else e.id = JOGO;

  COMECAR_HTML;

  switch (e.id) {
    case INICIO: drawMenu(&e); break;
    case SELECAO:
    case JOGO: drawJogo(&e); break;
  }

  FECHAR_HTML;

  return 0;
}
