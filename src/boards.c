#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "valida.h"

void fazTab(ESTADO *e)
{
  int jog;
  int i, j, sf;
  getScaleFactor(&sf, e);
  for (i = 0; i < e->num_lins; i++)
  {
    for (j = 0; j < e->num_cols; j++)
    {
      if (e->grelha[i][j] > FIXO_O)
      {
        jog = fromPair(i, j);
        push(e, jog, 0);
        drawPeca(i, j, e, sf, validaPeca(e, i, j));
        pop(e, 0);
        printf("%d\n", e->spU);
      }
      else
        drawPeca(i, j, e, sf, validaPeca(e, i, j));
    }
  }
}

ESTADO le_tabuleiro()
{
  ESTADO e;
  int nl, nc;
  int i,j;
  char linha[20];
  char nomef[MAX_PATH];

  sprintf(nomef, "%s%s", TAB_PATH, "tabuleiro3.txt");
  FILE *fp=fopen(nomef, "r");
  fscanf(fp, "%d %d", &nl, &nc); // possivel erro

  e.num_lins = nl;
  e.num_cols = nc;
  e.spU=e.spR=e.epR=e.epU=e.spA=e.epA=0;

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
