#include "historico.h"

void marcaAncora(ESTADO *e)
{
  e->numAncs++;
}

void voltaAncora(ESTADO *e)
{
  int x, y, a;
  if (e->numAncs > 0 && e->sizeU > 0) {
    do {
      fazUndo(e,&x,&y,&a);
    } while (e->sizeU && a == e->numAncs);
    if (e->sizeU)
        fazRedo(e, &x, &y, &a);
    e->numAncs--;
  }
}

void fazRedo(ESTADO *e, int *x, int *y, int *a)
{
  pop(x, y, a, &(e->redo));
  if (e->grelha[(*x)][(*y)] == SOL_O)
    e->grelha[(*x)][(*y)] = VAZIA;
  else e->grelha[(*x)][(*y)]++;
  push(*x, *y, *a, &(e->undo));
  if (*a > e->numAncs)
    e->numAncs++;
  e->sizeR--;
  e->sizeU++;
}

void fazUndo(ESTADO *e, int *x, int *y, int *a)
{
  pop(x, y, a, &(e->undo));
  switch(e->grelha[(*x)][(*y)]) {
    case HINT_X:
    case HINT_O:
    case SOL_X: e->grelha[(*x)][(*y)] = VAZIA;
                break;
    case SOL_O: e->grelha[(*x)][(*y)] = SOL_X;
                break;
    case VAZIA: e->grelha[(*x)][(*y)] = SOL_O;
                break;
  }
  push(*x, *y, *a, &(e->redo));
  e->sizeR++;
  e->sizeU--;
}
