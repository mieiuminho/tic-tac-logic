#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"

#define MAX_BUFFER  10240

char *estado2str(ESTADO e) {
  static char buffer[MAX_BUFFER];
  unsigned char *p = (unsigned char *) &e;
  int i;
  buffer[0] = 0;
  for(i = 0; i < (int) sizeof(ESTADO); i++)
    sprintf(buffer, "%s%02x", buffer, p[i]);

  return buffer;
}

ESTADO str2estado(char *argumentos) {
  ESTADO e;
  unsigned char *p = (unsigned char *) &e;
  int i;

  for(i = 0; i < (int) sizeof(ESTADO); i++, argumentos += 2) {
    unsigned d;
    sscanf(argumentos, "%2x", &d);
    p[i] = (unsigned char) d;
  }

  return e;
}

void getUserAndAction(char * link,char * user,char * action)
{
    int i,j=0;
    for (i=0;link[i]&&link[i]!='@';i++)
        user[i]=link[i];
    user[i]='\0';
    for (i=i+1;link[i];i++)
        action[j++]=link[i];
    action[j]='\0';
}

void push (int x,int y,LISTA * l)
{
    LISTA new;
    new = malloc(sizeof(struct lista));
    new->x=x;new->y=y;new->next=(*l);
    (*l)=new;
}

void addEnd (int x,int y,LISTA * l)
{
    LISTA new,pt,ant=NULL;
    new = malloc(sizeof(struct lista));
    pt = (*l);
    new->x=x;new->y=y;new->next=NULL;
    while (pt)
    {
        ant = pt;
        pt = pt->next;
    }
    if (ant) ant->next = new; else (*l) = new;
}

void pop (int * x,int * y,LISTA * l)
{
    LISTA temp;
    temp = (*l);
    *x = temp->x;
    *y = temp->y;
    (*l)=(*l)->next;
    free(temp);
}

void inicializar (ESTADO * e)
{
    int i,j;
    e->id=e->sizeU=e->sizeR=e->numAncs=0;
    e->num_cols=e->num_lins=3;
    for (i=0;i<e->num_cols;i++)
        for (j=0;j<e->num_lins;j++)
            e->grelha[i][j]=VAZIA;
    e->undo=NULL;
    e->redo=NULL;
    e->validade=1;
    e->tema=DEFAULT;
}



void writeFile (char * user,ESTADO e)
{
    FILE * fp;
    int i,j,x,y;
    char link [60];
    sprintf(link,"/var/www/html/utilizadores/%s.txt",user);
    fp = fopen(link,"w+");
    fprintf(fp,"%d %d %d %d %d\n",e.num_lins,e.num_cols,e.sizeU,e.sizeR,e.numAncs);
    for (j=0;j<e.num_lins;j++)
    {
        for(i=0;i<e.num_cols;i++)
            fprintf(fp,"%d ",(e.grelha[j][i]));
        fputc('\n',fp);
    }
    for(i=0;i<e.sizeU;i++)
    {
        pop(&x,&y,&(e.undo));
        fprintf(fp,"%d %d ",x,y);
    }
    fputc('\n',fp);
    for(i=0;i<e.sizeR;i++)
    {
        pop(&x,&y,&(e.redo));
        fprintf(fp,"%d %d ",x,y);
    }
    fprintf(fp,"\n%d",e.id);
    fprintf(fp,"\n%d",e.validade);
    fprintf(fp,"\n%d",e.tema);
    fclose(fp);
}


void readFile (char * user,ESTADO * e)
{
    int i,j,a,b;
    FILE * fp;
    e->undo=NULL;
    char link [60];
    sprintf(link,"/var/www/html/utilizadores/%s.txt",user);
    fp = fopen(link,"r+");
    if (fp)
    {
        fscanf(fp,"%d %d %d %d %d",&(e->num_lins),&(e->num_cols),&(e->sizeU),&(e->sizeR),&(e->numAncs));
        for (j=0;j<e->num_lins;j++)
            for(i=0;i<e->num_cols;i++)
                fscanf(fp,"%d",&(e->grelha[j][i]));
        for(i=0;i<e->sizeU;i++)
        {
            fscanf(fp,"%d %d",&a,&b);
            addEnd(a,b,&(e->undo));
        }
        for(i=0;i<e->sizeR;i++)
        {
            fscanf(fp,"%d %d",&a,&b);
            addEnd(a,b,&(e->redo));
        }
        fscanf(fp,"%d",&(e->id));
        fscanf(fp,"%d",&(e->validade));
        fscanf(fp,"%d",&(e->tema));
    }
    else
    {
        fp = fopen(link,"w+");
        inicializar(e);
    }

    fclose(fp);
}
