#include "historico.h"
#include "cgi.h"
#include "graphics.h"

void preparaHistorico(ESTADO * e,int iH)
{
  int i,inic;
  inic = iH ? (*e).compHistR : (*e).compHistU;
  if (iH)
    for (i=inic;i>0;i--)
      (*e).histR[i] = (*e).histR[i-1];
  else
    for (i=inic;i>0;i--)
      (*e).histU[i] = (*e).histU[i-1];

}

void adicionaHistorico(ESTADO * e,JOGADA j,int iH)
{
  if (iH)
  {
    if ((*e).compHistR<10)(*e).compHistR++;
    preparaHistorico(e,1);
    (*e).histR[0] = j;
  }
  else
  {
    if ((*e).compHistU<10)(*e).compHistU++;
    preparaHistorico(e,0);
    (*e).histU[0] = j;
  }
}

void retiraHistorico(ESTADO * e,int iH)
{
  int i;
  if (iH)
  {
    for (i=0;i<(*e).compHistR;i++)
      (*e).histR[i] = (*e).histR[i+1];
    if ((*e).compHistR>0) (*e).compHistR--;
  }
  else
  {
    for (i=0;i<(*e).compHistU;i++)
      (*e).histU[i] = (*e).histU[i+1];
    if ((*e).compHistU>0) (*e).compHistU--;
  }
}

void fazUndo(ESTADO * e)
{
  if((*e).compHistU)
  {
    JOGADA j;
    char pec,holder;
    j = (*e).histU[0];
    adicionaHistorico(e,j,1);
    pec = (j.peca==4) ? 3 : 4;
    holder = (*e).grelha[j.x][j.y];
    (*e).grelha[j.x][j.y] = pec;
    retiraHistorico(e,0);
    abrirLink(*e);
      IMAGEM_ABS(302,400,250,125,"undo.png");
    FECHAR_LINK;
    (*e).grelha[j.x][j.y] = holder;
     adicionaHistorico(e,j,0);
     retiraHistorico(e,1);
  }
  else IMAGEM_ABS(302,400,250,125,"undo.png");
}

void fazRedo(ESTADO * e)
{
  char holder;
  if((*e).compHistR)
  {
    JOGADA j;
    j = (*e).histR[0];
    holder = (*e).grelha[j.x][j.y];
    (*e).grelha[j.x][j.y] = j.peca;
    retiraHistorico(e,1);
    adicionaHistorico(e,j,0);
    abrirLink(*e);
      IMAGEM_ABS(1352,400,250,125,"redo.png");
    FECHAR_LINK;
    (*e).grelha[j.x][j.y] = holder;
    adicionaHistorico(e,j,1);
    retiraHistorico(e,0);
  }
  else IMAGEM_ABS(1352,400,250,125,"redo.png");
}
