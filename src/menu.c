#include "menu.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"

void drawMenu (ESTADO * e)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    IMAGEM_ABS(752,200,400,200, "title.png");
    drawButton(e, 852, 400, 200, 100, "play.png");
  FECHAR_SVG;
}

void drawJogo (ESTADO * e)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    IMAGEM_ABS(752, 0, 400, 200, "title.png");
    fazTab(e);
    fazUndo(e);
    fazRedo(e);
    fazAncoras(e);
  FECHAR_SVG;
}