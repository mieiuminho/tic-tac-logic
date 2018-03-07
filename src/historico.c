#include "historico.h"
#include "cgi.h"
#include "graphics.h"

void preparaHistorico(ESTADO * e)
{
  int i;
  for (i=(*e).compHist;i>0;i--)
    (*e).hist[i] = (*e).hist[i-1];
}

void adicionaHistorico(ESTADO * e,JOGADA j)
{
  if (j.x != (*e).hist[0].x && j.y != (*e).hist[0].y)
  {
    preparaHistorico(e);
    (*e).hist[0] = j;
    if ((*e).compHist < MAX_HIST) (*e).compHist++;
  }
  else (*e).hist[0].peca = j.peca;
}

void retiraHistorico(ESTADO * e)
{
  int i;
  for (i=1;i<(*e).compHist;i++)
    (*e).hist[i-1] = (*e).hist[i];
  if ((*e).compHist>0) (*e).compHist--;
}

void fazUndo(ESTADO * e)
{
  if((*e).compHist)
  {
    JOGADA j;
    j = (*e).hist[0];
    (*e).grelha[j.x][j.y] = VAZIA;
    retiraHistorico(e);
    abrirLink(*e);
    IMAGEM(0,0,50,"undo.png");
    FECHAR_LINK;
    adicionaHistorico(e,j);
  }
  else IMAGEM(0,0,50,"undo.png");
}

void fazRedo(ESTADO * e)
{
  if((*e).compHist)
  {
    JOGADA j;
    j = (*e).hist[0];
    (*e).grelha[j.x][j.y] = j.peca;
    retiraHistorico(e);
    abrirLink(*e);
    IMAGEM(0,3,50,"redo.png");
    FECHAR_LINK;
    adicionaHistorico(e,j);
  }
  else IMAGEM(0,3,50,"redo.png");
}