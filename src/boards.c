#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "valida.h"

void fazTab(ESTADO *e,char * user)
{
  int i, j, sf;
  getScaleFactor(&sf, e);
  for (i = 0; i < e->num_lins; i++)
    for (j = 0; j < e->num_cols; j++)
      if (e->grelha[i][j] > FIXO_O) drawPeca(i, j, e, sf, validaPeca(e, i, j),user);
      else drawPeca(i, j, e, sf, validaPeca(e, i, j),user);
}

ESTADO le_tabuleiro(ESTADO * a,int x)
{
  ESTADO e;
  e.tema=a->tema;
  int nl, nc;
  int i,j;
  char linha[20];
  char nomef[MAX_PATH];

  sprintf(nomef, "%s%s%d%s", TAB_PATH, "tabuleiro",x,".txt");
  FILE *fp=fopen(nomef, "r");
  fscanf(fp, "%d %d", &nl, &nc); // possivel erro

  e.num_lins = nl;
  e.num_cols = nc;
  e.sizeU=e.sizeR=e.numAncs=0;
  e.validade=1;
  e.undo=NULL;
  e.redo=NULL;

  for(i=0;i<nl;i++){
    fscanf(fp, "%s", linha);
    for(j=0;j<nc;j++)
      switch (linha[j]) {
        case 'X':
        case 'x': e.grelha[j][i] = FIXO_X;break;
        case 'O':
        case 'o': e.grelha[j][i] = FIXO_O;break;
        case '#': e.grelha[j][i] = BLOQUEADA;break;
        default : e.grelha[j][i] = VAZIA;
      }
  }
  return e;
}
