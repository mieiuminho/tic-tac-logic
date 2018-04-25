#include "historico.h"

void marcaAncora(ESTADO * e)
{
    e->numAncs++;
}

void voltaAncora(ESTADO * e)
{
    int x,y,a;
    if (e->numAncs>0&&e->sizeU>0)
    {
        do
        {
            pop(&x,&y,&a,&(e->undo));
            if (a==e->numAncs) {if (e->grelha[x][y]==VAZIA) e->grelha[x][y]=SOL_O; else e->grelha[x][y]--;}
            e->sizeU--;
        } while (e->sizeU&&a==e->numAncs);
        if (e->sizeU > 0) 
        {
            push(x,y,a,&(e->undo));
            e->sizeU++;
        }
        e->numAncs--;
    }
}