#include "valida.h"

/**
\brief Função que verifica se duas peças são iguais.
@param *e Apontador para o estado.
@param i Coordenada correspondente ao eixo dos xx da primeira peça.
@param j Coordenada correspondente ao eixo dos yy da primeira peça.
@param x Coordenada correspondente ao eixo dos xx da segunda peça.
@param y Coordenada correspondente ao eixo dos yy da segunda peça.
@returns "1" caso afirmativo ou "0" caso contrário.
*/
int isEqual (PUZZLE *board,int i, int j, int x, int y)
{
  int r = 0;

  switch (board->grelha[i][j]) {
    case FIXO_X:
    case SOL_X : r = (board->grelha[x][y] == SOL_X || board->grelha[x][y] == FIXO_X) ? 1 : 0;
                 break;
    case FIXO_O:
    case SOL_O : r = (board->grelha[x][y] == SOL_O || board->grelha[x][y] == FIXO_O) ? 1 : 0;
                 break;
  }

  return r;
}

int isOnTab (PUZZLE *board, int i, int j)
{
  int r = 1;

  if (i < 0 || i >= board->num_cols || j < 0 || j >= board->num_lins)
    r = 0;

  return r;
}

int validaJogada (PUZZLE *board, int i, int j)
{
  int pl, pc;
  int r = 1;

    for (pl = -1; pl <= 1 && r; pl++)
      for (pc = -1; pc <=1 && r; pc++)
        if ((pc || pl) && isOnTab (board, i+pc, j+pl)) {
          if (isEqual (board, i, j, i+pc, j+pl)) {
            if (isOnTab (board, i-pc, j-pl) && isEqual (board, i, j, i-pc, j-pl))
              r = 0;
            else if (isOnTab (board, i+2*pc, j+2*pl) && isEqual (board, i, j, i+2*pc, j+2*pl))
              r = 0;
          }
        }

  return r;
}

int validaPeca (PUZZLE * board,int i,int j)
{
  int r = 1, foundX = 0, foundO = 0;

  if (board->grelha[i][j] != VAZIA) r = validaJogada (board,i,j);
  else {
    board->grelha[i][j] = SOL_X;
    if (!validaJogada (board,i,j)) foundO=1;
    board->grelha[i][j] = SOL_O;
    if (!validaJogada (board,i,j)) foundX=1;
    board->grelha[i][j] = VAZIA;
    if (foundO && foundX) r = 2;
  }

  return r;
}

int validade (PUZZLE *board)
{
  int i, j, r = 1;
  for (i = 0; i < board->num_cols; i++)
    for (j = 0; j < board->num_lins; j++)
      if (validaPeca (board, i, j) == 0)
        r = 0;
  return r;
}

int isFull (PUZZLE * board)
{
  int i,j,r=1;
  for (i=0;i<board->num_cols&&r;i++)
    for (j=0;j<board->num_lins&&r;j++)
      if (board->grelha[i][j]==VAZIA) r = 0;
  return r;
}
