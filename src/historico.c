#include "historico.h"

void marcaAncora(ESTADO * e)
{
    push(99,99,&(e->undo));
    e->sizeU++;
    e->numAncs++;
}

void voltaAncora(ESTADO * e)
{
    int x,y;
    if (e->numAncs>0)
    {
        do
        {
            pop(&x,&y,&(e->undo));
            if (x!=99) {if (e->grelha[x][y]==VAZIA) e->grelha[x][y]=SOL_O; else e->grelha[x][y]--;}
            e->sizeU--;
        } while (x!=99);
        e->numAncs--;
    }
}