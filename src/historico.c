#include "historico.h"
#include "cgi.h"
#include "graphics.h"

int fromPair (int x,int y)
{
    x*=100;
    x+=y;
    return x;
}

void toPair (int * x,int * y,int num)
{
    if (num>=1000)
    {
        (*x)=num/1000;
        (*x)*=10;
        (*x)+=(num-((*x)*100))/100;
        (*y)=num - ((*x)*100);
    }
    else
    {
        (*x)=num/100;
        (*y)=num - ((*x)*100);
    }
}


void push(ESTADO * e,int jog,int iH)
{
  if (iH)
  {
    e->redo[e->spR % MAX_HISTR]=jog;
    if ((e->spR + 1)%MAX_HISTR == (e->epR)%MAX_HISTR) e->epR ++;
    e->spR++;
  }
  else
  {
    e->undo[e->spU % MAX_HISTU]=jog;
    if ((e->spU + 1)%MAX_HISTU == (e->epU)%MAX_HISTU) e->epU ++;
    e->spU++;
  }
}

void pop(ESTADO * e,int iH)
{
  if (iH)
  {
    if (e->spR>0&&(e->spR%MAX_HISTR != e->epR%MAX_HISTR)) e->spR--;
  }
  else
  {
    if (e->spU>0&&(e->spU%MAX_HISTU != e->epU%MAX_HISTU)) e->spU--;
  }
}

void fazUndo(ESTADO * e)
{
  if(e->spU>0&&(e->spU%MAX_HISTU != e->epU%MAX_HISTU))
  {
    int j,x,y;
    char pec,holder;
    j = e->undo[((e->spU-1)%MAX_HISTU)];
    push(e,j,1);
    toPair(&x,&y,j);
    holder = e->grelha[x][y];
    pec = (holder==4) ? 3 : 4;
    e->grelha[x][y] = pec;
    pop(e,0);
    abrirLink(*e);
      IMAGEM_ABS(302,400,250,125,"undo.png");
    FECHAR_LINK;
    e->grelha[x][y] = holder;
    push(e,j,0);
    pop(e,1);
  }
  else IMAGEM_ABS(302,400,250,125,"undo.png");
}

void fazRedo(ESTADO * e)
{
  char holder;
  if(e->spR>0&&(e->spR%MAX_HISTR != e->epR%MAX_HISTR))
  {
    int j,x,y;
    j = e->redo[((e->spR-1)%MAX_HISTR)];
    toPair(&x,&y,j);
    holder = e->grelha[x][y];
    e->grelha[x][y] = (holder==VAZIA) ? SOL_X : (holder+1);
    pop(e,1);
    push(e,j,0);
    abrirLink(*e);
      IMAGEM_ABS(1352,400,250,125,"redo.png");
    FECHAR_LINK;
    e->grelha[x][y] = holder;
    push(e,j,1);
    pop(e,0);
  }
  else IMAGEM_ABS(1352,400,250,125,"redo.png");
}
