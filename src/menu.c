#include "menu.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "solver.h"
#include "valida.h"
#include <string.h>

void drawStart(ESTADO *e, char *user)
{
  char path[60];
  colorSchemePath(e, path);
  if(strlen(user) == 0) ASK_USER;
    IMAGEM_ABS(752, 200, 400, 200, "title.png", path);
    drawButton(e, 852, 400, 200, 100, "play.png", "@id-1", user);
    drawButton(e, 10, 10, 75, 75, "palette.png", "@colorscheme", user);
}

void drawLobby(ESTADO *e, char *user)
{
  char path[60];
  colorSchemePath(e, path);
    drawButton(e, 10, 10, 75, 75, "arrow.png", "@id-0", user);
    drawButton(e, 10, 85, 75, 75, "palette.png", "@colorscheme", user);
    IMAGEM_ABS(752, 0, 400, 200, "title.png", path);
    drawButton(e, 652, 400, 200, 100, "easy.png", "@id-2", user);
    drawButton(e, 852, 400, 200, 100, "medium.png", "@id-3", user);
    drawButton(e, 1052, 400, 200, 100, "hard.png", "@id-4", user);
}

void drawLevel(ESTADO *e, char *user)
{
  int tab = 1;
  FILE *fp;
  char path[60];
  char level[60];
  char link[60];
  char action[40];
  colorSchemePath(e, path);
  boardLevelPath(e, level);
    drawButton(e, 10, 10, 75, 75, "arrow.png", "@id-1", user);
    drawButton(e, 10, 85, 75, 75, "palette.png", "@colorscheme", user);
    IMAGEM_ABS(752, 0, 400, 200, "title.png", path);
    do {
      sprintf(link, "%stabuleiro%d.txt", level, tab);
      fp = fopen(link, "r");
      if (fp != NULL) {
        sprintf(action, "%s%d", "@tab", tab);
          drawPreview(e, e->id, action, user, tab);
        fclose(fp);
      }
      tab++;
    } while (fp != NULL);
}

void drawGame(ESTADO *e, char *user)
{
  char path[60];
  colorSchemePath(e, path);
    drawButton(e, 10, 10, 75, 75, "arrow.png", "@id-1", user);
    drawButton(e, 10, 85, 75, 75, "palette.png", "@colorscheme", user);
    drawButton(e, 10, 160, 75, 75 , "hint.png", "@hint", user);
    drawButton(e, 10, 235, 75, 75, "solver.png", "@solve", user);
    setSemaforo(e);
    if (e->validade == VALIDO && isFull(e) == 1)
      drawButton(e, 727, 790, 450, 150, "parabens.png", "@id-1", user);
    else drawSemaforo(e);
    IMAGEM_ABS(752, 0, 400, 200, "title.png", path);
    fazTab(e, user);
    if (e->sizeU > 0)
      drawButton(e, 302, 400, 250, 125, "undo.png", "@undo", user);
    else
      IMAGEM_ABS(302,400,250,125,"undo.png",path);
    if (e->sizeR > 0)
      drawButton(e, 1352, 400, 250, 125, "redo.png", "@redo", user);
    else
      IMAGEM_ABS(1352,400,250,125,"redo.png",path);
    if (e->sizeU > 0 && e->undo->a > 0)
      drawButton(e, 302, 530, 250, 125, "voltar.png", "@voltar", user);
    else IMAGEM_ABS(302, 530, 250, 125, "voltar.png", path);
    drawButton(e, 1352, 530, 250, 125, "carregar.png", "@ancorar", user);
}
