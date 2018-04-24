#include "menu.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "solver.h"
#include "valida.h"
#include <string.h>

void drawMenu (ESTADO * e, char * user)
{
  char path[60];
  colorSchemePath(e,path);
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    IMAGEM_ABS(752, 200, 400, 200, "title.png", path);
    drawButton(e,852, 400, 200, 100, "play.png","@id-1",user);
    drawButton(e,10,10,75,75,"palette.png","@colorscheme",user);
  FECHAR_SVG;
}

void drawSelecao (ESTADO * e, char * user)
{
  char path[60];
  colorSchemePath(e,path);
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    drawButton(e, 10, 10, 75, 75, "arrow.png", "@id-0", user);
    drawButton(e, 10, 85, 75, 75, "palette.png", "@colorscheme", user);
    IMAGEM_ABS(752, 0, 400, 200, "title.png",path);
    drawButton(e, 652, 400, 200, 100, "hard.png","@tab1",user);
    drawButton(e, 852, 400, 200, 100, "easy.png","@tab2",user);
    drawButton(e, 1052, 400, 200, 100, "medium.png","@tab3",user);
  FECHAR_SVG;
}

void drawJogo (ESTADO * e, char * user)
{
  char path[60];
  colorSchemePath(e,path);
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    drawButton(e, 10, 10, 75, 75, "arrow.png", "@id-1", user);
    drawButton(e, 10, 85, 75, 75, "palette.png", "@colorscheme", user);
    drawButton(e, 10, 160, 75, 75 , "hint.png", "@hint", user);
    setSemaforo (e);
    drawSemaforo (e);
    IMAGEM_ABS(752, 0, 400, 200, "title.png", path);
    fazTab(e,user);
    drawButton(e, 302, 400, 250, 125, "undo.png", "@undo", user);
    drawButton(e, 1352, 400, 250, 125, "redo.png", "@redo", user);
    drawButton(e, 302, 530, 250, 125, "voltar.png", "@voltar", user);
    drawButton(e, 1352, 530, 250, 125, "carregar.png", "@carregar", user);
  FECHAR_SVG;
}
