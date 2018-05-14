#include <stdlib.h>
#include <stdio.h>
#include "historico.h"
#include "puzzle.h"
#include "solver.h"
#include "valida.h"

void supor (PUZZLE * board,int * found)
{
  int x,y,tmp;
  marcaAncora(board);
  while ((*found )==0)
  {
    tmp = solver_easy (board, &x, &y);
    if (tmp == 1)
    {
      push(x, y, board->numAncs, &(board->undo));
      board->sizeU++;
    }
    else if (tmp == 2) {board->grelha[x][y]=VAZIA;*found=2;}
         else if (tmp==0) *found=1;
  }
}

int solver_hard (PUZZLE *board)
{
  int i, j, found,foundX,foundO;
  found=foundX=foundO=0;

  for (i = 0; (i < board->num_cols) && !found; i++)
    for (j = 0; (j < board->num_lins) && !found; j++)
      if (board->grelha[i][j] == VAZIA)
      {
        board->grelha[i][j] = SOL_O;
        found=0;
        supor(board,&found);
        if (found == 2)
          foundX=1;
        voltaAncora (board);
        found = 0;
        board->grelha[i][j] = SOL_X;
        supor(board,&found);
        if (found == 2)
            foundO=1;
        if (foundX && foundO) {board->grelha[i][j]=BLOQUEADA;found=0;}
        else if (foundX) {board->grelha[i][j]=SOL_X;found=1;}
             else if (foundO)  {board->grelha[i][j]=SOL_O;found=1;}
                  else {board->grelha[i][j]=VAZIA;found=0;}
        voltaAncora(board);
        }
    return found;
}


int solver_easy (PUZZLE *board, int *x, int *y)
{
    int i, j, found, foundX, foundO;
    i = j = found = foundX = foundO = 0;
    for (i = 0; i < board->num_cols && !found; i++)
        for (j = 0; j < board->num_lins && !found; j++)
          if (board->grelha[i][j] == VAZIA) {
            board->grelha[i][j] = SOL_X;
            if (!validaPeca (board, i, j))
              foundO = 1;

            board->grelha[i][j] = SOL_O;
            if (!validaPeca (board, i, j))
              foundX = 1;

            if (foundX && foundO) {
              found = 2;
              *x = i; *y = j;
              board->grelha[i][j] = BLOQUEADA;
            } else if (foundX) {
              board->grelha[i][j] = SOL_X;
              found = 1;
              *x = i; *y = j;
            } else if (foundO) {
              board->grelha[i][j] = SOL_O;
              found = 1;
              *x = i; *y = j;
            } else board->grelha[i][j] = VAZIA;
          }
    return found;
}

void randomPlay (PUZZLE *board)
{
  int x, y, k,flag=1;
  k = rand() % 2;

  while (flag)
  {
    x = rand() % board->num_cols;
    y = rand() % board->num_lins;
    if (board->grelha[x][y] == VAZIA)
    {
      board->grelha[x][y] = k ? FIXO_X : FIXO_O;flag=0;
    if (!validaPeca(board,x,y))
    {
      if (k) board->grelha[x][y]=FIXO_O;
      else board->grelha[x][y]=FIXO_X;
    }
    if(!validaPeca(board,x,y))
      board->grelha[x][y]=BLOQUEADA;
    }
  }
}


void randomBloqPlay (PUZZLE *board)
{
  int x, y, flag = 1;

  while (flag)
  {
    x = rand() % board->num_cols;
    y = rand() % board->num_lins;
    if (board->grelha[x][y] == VAZIA) flag=0;
  }
  board->grelha[x][y] = BLOQUEADA;
}

int solutions (PUZZLE board)
{
  int i, j, r;
  i = j = r = 0;

  if (validade(&board) == 1) {
    if (isFull(&board) == 1)
      r = 1;
    else {
      for (; i < board.num_cols && board.grelha[i][j] != VAZIA; i++)
        for (; j < board.num_lins && board.grelha[i][j] != VAZIA; j++);
      board.grelha[i][j] = SOL_O;
      r += solutions(board);
      board.grelha[i][j] = SOL_X;
      r += solutions(board);
    }
  }

  return r;
}
