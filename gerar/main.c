/**
@file main.c
Esqueleto do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "generator.h"
#include "puzzle.h"
#include "solver.h"

/**
\brief Função que converte os números recebidos na chamada do programa,
sob a forma de "char", em inteiros.
@param *num String recebida.
*/
int string2int (char const *num)
{
  int r = 0;
  while (*num != '\0' && *num >= '0' && *num <= '9') {
    r += *num - '0';
    num++;
    r *= 10;
  }
  r /= 10;
  return r;
}

/**
\brief Função que desenha o tabuleiro no terminal.
@param *board Apontador para o tabuleiro.
*/
void showBoard (PUZZLE *board)
{
  int i, j;
  char c;
  for (i = 0; i < board->num_lins; i++)
  {
    for (j = 0; j < board->num_cols; j++)
    {
      switch (board->grelha[j][i])
      {
        case FIXO_X:    c = 'X'; break;
        case FIXO_O:    c = 'O'; break;
        case BLOQUEADA: c = '#'; break;
        default: c = '.';
      }
      putchar(c);
    }
    putchar('\n');
  }
}

/**
\brief Função que cria um tabuleiro com o tamanho recebido nos argumentos
sendo todas as peças "VAZIA".
@param *board Apontador para o tabuleiro.
*/
void tudoVazia (PUZZLE *board)
{
  int i, j;
  for (i = 0; i < board->num_cols; i++)
    for (j = 0; j < board->num_lins; j++)
      board->grelha[i][j] = VAZIA;
}

/**
\brief Função que substitui peças jogadas por peças vazias.
@param *board Apontador para o tabuleiro.
*/
void retiraSols (PUZZLE *board)
{
  int i,j;
  for (i = 0; i < board->num_cols; i++)
            for (j = 0; j < board->num_lins; j++)
              switch(board->grelha[i][j])
              {
                case SOL_X:
                case SOL_O: board->grelha[i][j] = VAZIA;
                            break;
              }
}

/**
\brief Função que escreve o tabuleiro num ficheiro.
@param *fp Apontador para o ficheiro.
@param *board Apontador para o tabuleiro.
*/
void writeBoard (FILE *fp, PUZZLE *board)
{
  int i,j;
  char c;
  fprintf(fp, "%d %d\n", board->num_lins, board->num_cols);
  for (i = 0 ; i < board->num_lins; i++)
  {
    for (j = 0; j < board->num_cols; j++)
    {
      switch (board->grelha[j][i])
      {
        case FIXO_X:    c = 'X'; break;
        case FIXO_O:    c = 'O'; break;
        case BLOQUEADA: c = '#'; break;
        default: c = '.';
      }
      fputc(c,fp);
    }
    fputc('\n',fp);
  }
}

/**
\brief Função que guarda o tabuleiro na diretoria certa de acordo
com a dificuldade.
@param *board Apontador para o tabuleiro.
@param dif Identificador da dificuldade.
*/
void saveBoard (PUZZLE *board, int dif)
{
  char diretoria[6];
  char nomeTab[30];
  if (dif == 1) sprintf(diretoria,"easy/");
  else sprintf(diretoria,"hard/");
  int i = 1, notFoundTab = 1;
  FILE *fp;
  while (notFoundTab)
  {
    sprintf(nomeTab,"%stabuleiro%d.txt",diretoria,i);
    fp = fopen(nomeTab,"r+");
    if (fp) {fclose(fp);i++;}
    else
    {
      fp=fopen(nomeTab,"w+");
      notFoundTab = 0;
      writeBoard(fp,board);
    }
  }
}

/**
\brief Função motora do processo de gerar tabuleiros.
*/
int main (int argc, char const *argv[])
{
    PUZZLE board;
    int nl, nc, dif;
    if (argc == 4)
    {
      srand(time(NULL));
      dif = string2int (argv[1]);
      nl  = string2int (argv[2]);
      nc  = string2int (argv[3]);
      if (nl > 0 && nc > 0 && (dif == 1 || dif == 2) && nl <= 20 && nc <= 20)
      {
        board.num_lins = string2int (argv[2]);
        board.num_cols = string2int (argv[3]);
        board.sizeR = board.sizeU = board.numAncs = 0;
        board.undo = board.redo = NULL;
        tudoVazia(&board);
        geraTabuleiro(&board,dif);
        retiraSols(&board);
        showBoard(&board);
        saveBoard(&board,dif);
      }
      else
        printf("Este programa recebe exatamente três argumentos.\n<dificuldade> <número de linhas> <número de colunas>\n");
    } else
        printf("Este programa recebe exatamente três argumentos.\n<dificuldade> <número de linhas> <número de colunas>\n");
  return 0;
}
