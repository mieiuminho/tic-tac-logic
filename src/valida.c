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
int isEqual (ESTADO * e,int i,int j,int x,int y)
{
  int r=0;
  switch (e->grelha[i][j])
  {
    case FIXO_X:
    case HINT_X:
    case SOL_X : r = (e->grelha[x][y]==SOL_X || e->grelha[x][y]==FIXO_X || e->grelha[x][y]==HINT_X) ? 1 : 0;break;
    case FIXO_O:
    case HINT_O:
    case SOL_O : r = (e->grelha[x][y]==SOL_O || e->grelha[x][y]==FIXO_O || e->grelha[x][y]==HINT_O) ? 1 : 0;break;
  }
  return r;
}

int isOnTab (ESTADO * e,int i,int j)
{
  int ret=1;
  if (i<0 || i>=(e->num_cols) || j<0 || j>=(e->num_lins)) ret=0;
  return ret;
}

int validaJogada (ESTADO * e,int i, int j)
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

int validaPeca (ESTADO * e,int i,int j)
{
  int r=1,foundX=0,foundO=0;
  if (e->grelha[i][j]!=VAZIA) r = validaJogada(e,i,j);
  else
  {
    e->grelha[i][j]=SOL_X;
    if (!validaJogada(e,i,j)) foundO=1;
    e->grelha[i][j]=SOL_O;
    if (!validaJogada(e,i,j)) foundX=1;
    e->grelha[i][j]=VAZIA;
    if (foundO&&foundX) r=2;
  }
  return r;
}

void setSemaforo (ESTADO * e)
{
  int i,j,r=1,foundInc=0;
  for (i=0;i<e->num_cols&&r!=0;i++)
  {
    for (j=0;j<e->num_lins&&r!=0;j++)
    {
      r = validaPeca(e,i,j);
      if (r==2) foundInc = 1;
    }
  }
  if (r==0) e->validade = INVALIDO;
  else e->validade = foundInc ? IMPOSSIVEL : VALIDO;
}

int isFull(ESTADO *e)
{
  int i, j, r = 1;
  for (i = 0; i < e->num_cols && r; i++)
    for (j = 0; j < e->num_lins && r; j++)
      if (e->grelha[i][j] == VAZIA)
        r = 0;
  return r;
}