#include "valida.h"

int isEqual (ESTADO * e,int i,int j,int x,int y)
{
  int r=0;
  switch (e->grelha[i][j])
  {
    case FIXO_X:
    case SOL_X : r = (e->grelha[x][y]==SOL_X || e->grelha[x][y]==FIXO_X) ? 1 : 0;break;
    case FIXO_O:
    case SOL_O : r = (e->grelha[x][y]==SOL_O || e->grelha[x][y]==FIXO_O) ? 1 : 0;break;
  }
  return r;
}

int isOnTab (ESTADO * e,int i,int j)
{
  int ret=1;
  if (i<0 || i>=(e->num_cols) || j<0 || j>=(e->num_lins)) ret=0;
  return ret;
}

int validaPeca (ESTADO * e,int i, int j)
{
  int pl,pc;
  int r = 1;
  for(pl=-1;pl<=1&&r;pl++)
  {
    for(pc=-1;pc<=1&&r;pc++)
    {
      if((pc||pl) && isOnTab(e,i+pc,j+pl))
      {
        if (isEqual(e,i,j,i+pc,j+pl))
        {
          if (isOnTab(e,i-pc,j-pl) && isEqual(e,i,j,i-pc,j-pl)) r = 0;
          else if(isOnTab(e,i+2*pc,j+2*pl) && isEqual(e,i,j,i+2*pc,j+2*pl)) r = 0;
        }
      }
    }
  }

  return r;
}

int isPossible (ESTADO *e)
{
  int i, j, r=1, counter=0;
  char holder;
  for(i=0;i<e->num_lins && r==1;i++)
  {
    for(j=0;j<e->num_cols && r==1;j++)
    {
      if(e->grelha[i][j]==VAZIA)
      {
        holder=e->grelha[i][j];
        e->grelha[i][j]=SOL_X;
        if(!(validaPeca(e,i,j))) counter+=1;
        e->grelha[i][j]=SOL_O;
        if(!(validaPeca(e,i,j))) counter+=1;
        e->grelha[i][j]=holder;
        if(counter==2)
        {
          r=0;
          break;
        }
      }
    }
  }
  return r;

}


























