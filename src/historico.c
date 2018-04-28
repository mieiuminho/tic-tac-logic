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
            if (a==e->numAncs)
            {
                switch(e->grelha[x][y])
                {
                    case HINT_X:
                    case HINT_O:
                    case SOL_X:e->grelha[x][y]=VAZIA;break;
                    case SOL_O:e->grelha[x][y]=SOL_X;break;
                    case VAZIA:e->grelha[x][y]=SOL_O;break;
                }
            }
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
