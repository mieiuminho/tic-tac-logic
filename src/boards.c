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
  for (i = 0; i < e->num_cols; i++)
    for (j = 0; j < e->num_lins; j++)
      drawPeca(i, j, e, sf, validaPeca(e, i, j),user,0,0);
}

void boardLevelPath (ESTADO * e, char * level)
{
  switch(e->id)
  {
    case EASY:   sprintf(level,"%s%s/",TAB_PATH,"easy");
                 break;
    case MEDIUM: sprintf(level,"%s%s/",TAB_PATH,"medium");
                 break;
    case HARD:   sprintf(level,"%s%s/",TAB_PATH,"hard");
                 break;
  }
}


ESTADO le_tabuleiro(ESTADO *a, int x)
{
  ESTADO e;
  e.tema = a->tema;
  int nl, nc;
  int i, j;
  char linha[20];
  char nomef[MAX_PATH];
  char level[60];
  boardLevelPath(a,level);
  sprintf(nomef, "%stabuleiro%d.txt", level, x);
  FILE *fp=fopen(nomef, "r");
  if (fscanf(fp,"%d %d", &nl, &nc) == 2){
    e.num_lins = nl;
    e.num_cols = nc;
    e.sizeU = e.sizeR = e.numAncs = 0;
    e.validade = VALIDO;
    e.undo = NULL;
    e.redo = NULL;
  }
  for(i = 0; i < nl; i++) {
    if (fscanf(fp, "%s", linha)==1) {
      for(j = 0; j < nc; j++)
        switch (linha[j]) {
          case 'X':
          case 'x': e.grelha[j][i] = FIXO_X;break;
          case 'O':
          case 'o': e.grelha[j][i] = FIXO_O;break;
          case '#': e.grelha[j][i] = BLOQUEADA;break;
          default : e.grelha[j][i] = VAZIA;
        }
    }
  }
  return e;
}
