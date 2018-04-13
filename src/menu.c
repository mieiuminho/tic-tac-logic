#include "menu.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"

void drawMenu ()
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    IMAGEM_ABS(752, 200, 400, 200, "title.png");
    drawButtonABS("puzzles", 852, 400, 200, 100, "play.png");
  FECHAR_SVG;
}

void drawSelecao (ESTADO * e)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    drawButtonABS("", 10, 10, 75, 75, "arrow.png");
    IMAGEM_ABS(752, 0, 400, 200, "title.png");
    drawButtonABS("puzzles/1",  652, 400, 200, 100, "hard.png");
    drawButtonABS("puzzles/2",  852, 400, 200, 100, "easy.png");
    drawButtonABS("puzzles/3", 1052, 400, 200, 100, "medium.png");
  FECHAR_SVG;
}

void drawJogo (ESTADO * e)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    drawButtonABS("puzzles", 10, 10, 75, 75, "arrow.png");
    IMAGEM_ABS(752, 0, 400, 200, "title.png");
    fazTab(e);
    fazUndo(e);
    fazRedo(e);
    fazAncoras(e);
  FECHAR_SVG;
}