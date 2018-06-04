#include "solver.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "menu.h"
#include "valida.h"

void supor (ESTADO * e,int * notfound)
{
  int x,y;
  marcaAncora(e);
  while(*notfound==1)
  {
    *notfound=fillIn(e,&x,&y);
    if (*notfound==1) {push(x,y,e->numAncs,&(e->undo));e->sizeU++;}
  }
}

int findImpossible(ESTADO * e)
{
  int i,j,notfound;
  notfound=1;
  for (i=0;(i<e->num_cols)&&(notfound!=2);i++)
  {
    for (j=0;(j<e->num_lins)&&(notfound!=2);j++)
    {
      if (e->grelha[i][j]==VAZIA)
      {
        e->grelha[i][j]=HINT_O;
        supor(e,&notfound);
        if (notfound==2)
          e->grelha[i][j]=HINT_X;
        else
        {
          voltaAncora(e);
          notfound=1;
          e->grelha[i][j]=HINT_X;
          supor(e,&notfound);
          if (notfound==2)
            e->grelha[i][j]=HINT_O;
          else
          {
            e->grelha[i][j]=VAZIA;
            notfound=1;
          }
        }
        voltaAncora(e);
      }
    }
  }
  return notfound;
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
  setSemaforo(e);
  while ((!isFull(e)) && e->validade==VALIDO)
  {
    while (fillIn(e,&x,&y));
    setSemaforo(e);
    findImpossible(e);
    setSemaforo(e);
  }
}