#include "menu.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "solver.h"
#include "valida.h"

void drawMenu (char * user)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    IMAGEM_ABS(752, 200, 400, 200, "title.png");
    drawButton(852, 400, 200, 100, "play.png","@id-1",user);
  FECHAR_SVG;
}

void drawSelecao (char * user)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    drawButton(10, 10, 75, 75, "arrow.png","@id-0",user);
    IMAGEM_ABS(752, 0, 400, 200, "title.png");
    drawButton(652, 400, 200, 100, "hard.png","@tab1",user);
    drawButton(852, 400, 200, 100, "easy.png","@tab2",user);
    drawButton(1052, 400, 200, 100, "medium.png","@tab3",user);
  FECHAR_SVG;
}

void drawJogo (ESTADO * e, char * user)
{
  ABRIR_SVG(ECRA_X, ECRA_Y, "#000");
    drawButton(10, 10, 75, 75, "arrow.png","@id-1",user);
    setSemaforo (e);
    drawSemaforo (e);
    IMAGEM_ABS(752, 0, 400, 200, "title.png");
//    fillIn(e);
    fazTab(e,user);
    drawButton(302,400,250,125,"undo.png","@undo",user);
    drawButton(1352,400,250,125,"redo.png","@redo",user);
    drawButton(302,530,250,125,"voltar.png","@voltar",user);
    drawButton(1352,530,250,125,"carregar.png","@carregar",user);
  FECHAR_SVG;
}
