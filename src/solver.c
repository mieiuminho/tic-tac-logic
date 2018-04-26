#include "solver.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "menu.h"
#include "valida.h"

void findImpossible(ESTADO * e)
{
  int i,j,notfound,x,y;
  notfound=1;
  for (i=0;(i<e->num_lins)&&(notfound!=2);i++)
  {
    for (j=0;(j<e->num_cols)&&(notfound!=2);j++)
    {
      if (e->grelha[i][j]==VAZIA)
      {
        e->grelha[i][j]=HINT_O;
        marcaAncora(e);
        while(notfound==1)
        {
          notfound=fillIn(e,&x,&y);
          if (notfound==1) {push(x,y,e->numAncs,&(e->undo));e->sizeU++;}
        }
        if (notfound==2)
          e->grelha[i][j]=HINT_X;
        else
        {
          voltaAncora(e);
          notfound=1;
          e->grelha[i][j]=HINT_X;
          marcaAncora(e);
          while(notfound==1)
          {
            notfound=fillIn(e,&x,&y);
            if (notfound==1) {push(x,y,e->numAncs,&(e->undo));e->sizeU++;}
          }
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
}

// Função que percorre o tabuleiro e preenche com os casos imediatos
int fillIn (ESTADO * e,int * x,int * y)
{
    int i, j, found,foundX,foundO;
    i=j=found=foundX=foundO=0;
    for(i=0;(i<e->num_lins)&&(!found);i++)
    {
        for(j=0;(j<e->num_cols)&&(!found);j++)
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
  for(i=0;i<e->num_lins;i++)
  {
    for(j=0;j<e->num_cols;j++)
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

