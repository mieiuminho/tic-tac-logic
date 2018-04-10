#include "graphics.h"
#include "cgi.h"
#include <string.h>

void abrirLink (ESTADO * e)
{
  char link [MAX_BUFFER];
  sprintf(link,"http://localhost/cgi-bin/GandaGalo?%s\n",estado2str(*e));
  ABRIR_LINK(link);
}

void getScaleFactor(int * sf, ESTADO * e)
{
  *sf= (e->num_lins >= e->num_cols) ? (float) (DTAB/e->num_lins) : (float) (DTAB/e->num_cols);
}

void calculaCentroPeca (ESTADO * e,int sf,int * fx,int * fy)
{
  int cx = ((ECRA_X-DTAB)/2)-1,cy = ((ECRA_Y-DTAB)/2)-1,fnsx,fnsy; //fns = fix non square
  fnsx = (DTAB - (e->num_lins*sf))/2;
  fnsy = (DTAB -(e->num_cols*sf))/2;
  *fx = cx + fnsx;
  *fy = cy + fnsy;
}

void butaoProxEstadoJog (ESTADO * e,int i,int j,int sf,char * s)
{
  char holder;
  int cx,cy;
  calculaCentroPeca(e,sf,&cx,&cy);
  holder = e->grelha[i][j];
  MUDA_SEGUINTE(i,j,e);
  abrirLink(e);
  IMAGEM(i+cx,j+cy,sf,s);
  FECHAR_LINK;
  e->grelha[i][j] = holder;
}

void drawBloq (ESTADO * e,int i,int j,int sf,char * s)
{
  int cx,cy;
  calculaCentroPeca(e,sf,&cx,&cy);
  IMAGEM(i+cx,j+cy,sf,s);
}

void drawButton(ESTADO * e,int x,int y,int sx,int sy,char * s)
{
  abrirLink(e);
    IMAGEM_ABS(x,y,sx,sy,s);
  FECHAR_LINK;
}

/**
Coloca a imagem correspondente no local indicado
@param A posição x e y onde a imagem vai ser colocada assim como um char para identificar qual será essa imagem
*/
void drawPeca (int i,int j,ESTADO * e,int sf,int vPeca)
{
  char s[50];

  switch (e->grelha[i][j]) {
    case VAZIA:
                  strcpy(s,"vazio.png");
                  break;
    case SOL_X:
                  if (vPeca) strcpy(s,"X.png");
                  else strcpy(s,"wrongX.png");
                  break;
    case SOL_O:
                  if (vPeca) strcpy(s,"O.png");
                  else strcpy(s,"wrongO.png");
                  break;
    case FIXO_O:
                  if (vPeca) strcpy(s,"bloqO.png");
                  else strcpy(s,"wrongbloqO.png");
                  break;
    case FIXO_X:
                  if (vPeca) strcpy(s,"bloqX.png");
                  else strcpy(s,"wrongbloqX.png");
                  break;
    case BLOQUEADA: strcpy(s,"bloq.png");break;
  }

  if (e->grelha[i][j]>FIXO_O) butaoProxEstadoJog(e,i,j,sf,s);
  else drawBloq(e,i,j,sf,s);
}
