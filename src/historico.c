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
      drawButton(e,302,400,250,125,"undo.png");
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
      drawButton(e,1352,400,250,125,"redo.png");
    e->grelha[x][y] = holder;
    push(e,j,1);
    pop(e,0);
  }
  else IMAGEM_ABS(1352,400,250,125,"redo.png");
}

void saveAncora(ESTADO * e,short int x)
{
  e->ancoras[e->spA % MAX_HISTA]=x;
  if ((e->spA + 1)%MAX_HISTA == (e->epA)%MAX_HISTA) e->epA ++;
  e->spA++;
}

void deleteAncora(ESTADO * e)
{
  if (e->spA>0&&(e->spA%MAX_HISTA != e->epA%MAX_HISTA)) e->spA--;
}

void fUndoA(ESTADO * e,short int aux [],int n)
{
  int i,x,y,j;
  char pec;
  for (i=0;i<n;i++)
    {
    j = e->undo[((e->spU-1)%MAX_HISTU)];
    toPair(&x,&y,j);
    pec = (e->grelha[x][y]==4) ? 3 : 4;
    e->grelha[x][y] = pec;
    pop(e,0);
    aux[i]=j;
    }
}

void rUndoA(ESTADO * e,short int aux [],int n)
{
  int i,j,x,y;
  for (i=n-1;i>=0;i--)
    {
    j=aux[i];
    push(e,j,0);
    toPair(&x,&y,j);
    e->grelha[x][y] = (e->grelha[x][y]==5) ? 3 : e->grelha[x][y]+1;
    }
}

void fazAncoras(ESTADO * e)
{
  int dif=0,holder;
  if (e->spA>0&&(e->spA%MAX_HISTA != e->epA%MAX_HISTA)) dif = e->spU - e->ancoras[((e->spA-1)%MAX_HISTA)];
  short int aux [dif];
  if (e->spA>0&&(e->spA%MAX_HISTA != e->epA%MAX_HISTA))
  {
    holder=e->ancoras[(e->spA -1)%MAX_HISTA];
    fUndoA(e,aux,dif);
    deleteAncora(e);
    e->spR=e->epR=0;
      drawButton(e,952,800,200,100,"voltar.png");
    saveAncora(e,holder);
    rUndoA(e,aux,dif);
  }
  else IMAGEM_ABS(952,800,200,100,"voltar.png");



  saveAncora(e,e->spU);
    drawButton(e,752,800,200,100,"carregar.png");
  deleteAncora(e);
}


