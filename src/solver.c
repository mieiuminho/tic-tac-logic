#include "solver.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "menu.h"
#include "valida.h"

void supor (ESTADO *e,int *found)
{
  int x,y,tmp;
  marcaAncora(e);
  while ((*found )==0)
  {
    tmp = fillIn (e, &x, &y);
    if (tmp == 1)
    {
      push(x, y, e->numAncs, &(e->undo));
      e->sizeU++;
    }
    else if (tmp == 2) {e->grelha[x][y]=VAZIA;*found=2;}
         else if (tmp==0) *found=1;
  }
}

int findImpossible (ESTADO *e)
{
  int i, j, found,foundX,foundO;
  found=foundX=foundO=0;

  for (i = 0; (i < e->num_cols) && !found; i++)
    for (j = 0; (j < e->num_lins) && !found; j++)
      if (e->grelha[i][j] == VAZIA)
      {
        e->grelha[i][j] = SOL_O;
        found=0;
        supor(e,&found);
        if (found == 2)
          foundX=1;
        voltaAncora (e);
        found = 0;
        e->grelha[i][j] = SOL_X;
        supor(e,&found);
        if (found == 2)
            foundO=1;
        if (foundX && foundO) {e->grelha[i][j]=BLOQUEADA;found=0;}
        else if (foundX) {e->grelha[i][j]=SOL_X;found=1;}
             else if (foundO)  {e->grelha[i][j]=SOL_O;found=1;}
                  else {e->grelha[i][j]=VAZIA;found=0;}
        voltaAncora(e);
        }
    return found;
}

// Função que percorre o tabuleiro e preenche com os casos imediatos
int fillIn (ESTADO * e,int * x,int * y)
{
    int i, j, found,foundX,foundO;
    i=j=found=foundX=foundO=0;
    for(i=0;(i<e->num_cols)&&(!found);i++)
    {
        for(j=0;(j<e->num_lins)&&(!found);j++)
        {
          if(e->grelha[i][j]==VAZIA)
          {
            e->grelha[i][j]=SOL_X;
            if (!validaPeca(e,i,j))
              foundO=1;
            e->grelha[i][j]=SOL_O;
            if (!validaPeca(e,i,j))
              foundX=1;
            if (foundX&&foundO) {found=2;e->grelha[i][j]=VAZIA;}
            else if (foundX) {e->grelha[i][j]=HINT_X;found=1;*x=i;*y=j;}
                 else if (foundO) {e->grelha[i][j]=HINT_O;found=1;*x=i;*y=j;}
                      else e->grelha[i][j]=VAZIA;
          }

        }
    }
    return found;
}


void remHints (ESTADO * e)
{
  int i, j;
  for(i=0;i<e->num_cols;i++)
  {
    for(j=0;j<e->num_lins;j++)
    {
      switch(e->grelha[i][j])
      {
        case HINT_X: e->grelha[i][j]=SOL_X;
                     break;
        case HINT_O: e->grelha[i][j]=SOL_O;
                     break;
      }
    }
  }
}

void completaTabuleiro (ESTADO * e)
{
  int x,y;
  while ((!isFull(e)) && e->validade==VALIDO)
  {
    while (fillIn(e,&x,&y));
    findImpossible(e);
  }
}