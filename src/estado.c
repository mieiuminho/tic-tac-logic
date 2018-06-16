#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"

#define MAX_BUFFER  10240

void getUserAndAction(char *link, char *user, char *action)
{
    int i, j = 0;
    for (i = 0; link[i] && link[i] != '@'; i++)
        user[i] = link[i];
    user[i] = '\0';
    for (i = i+1; link[i]; i++)
        action[j++] = link[i];
    action[j] = '\0';
}

void push(int x, int y, int a, LISTA *l)
{
    LISTA new;
    new = malloc(sizeof(struct lista));
    new->x = x; new->y = y; new->a = a; new->next = *l;
    *l = new;
}

void addEnd(int x, int y, int a, LISTA *l)
{
    LISTA new, pt, ant = NULL;
    new = malloc(sizeof(struct lista));
    pt = *l;
    new->x = x; new->y = y; new->a = a; new->next = NULL;
    while (pt)
    {
        ant = pt;
        pt = pt->next;
    }
    if (ant) ant->next = new; else *l = new;
}

void pop(int *x, int *y, int *a, LISTA *l)
{
    LISTA temp;
    temp = *l;
    *x = temp->x;
    *y = temp->y;
    *a = temp->a;
    *l = (*l)->next;
    free(temp);
}

void inicializar(ESTADO *e)
{
    int i, j;
    e->id = e->sizeU = e->sizeR = e->numAncs = 0;
    e->num_cols = e->num_lins = 3;
    for (i = 0; i < e->num_cols; i++)
        for (j = 0; j < e->num_lins; j++)
            e->grelha[i][j] = VAZIA;
    e->undo = NULL;
    e->redo = NULL;
    e->validade = 1;
    e->tema = DEFAULT;
}

void writeFile(char *user, ESTADO e)
{
    FILE *fp;
    int i, j, x, y, a;
    char c;
    char link[60];
    sprintf(link, "/var/www/html/utilizadores/%s.txt", user);
    fp = fopen(link, "w+");
    fprintf(fp,"%d %d %d %d %d\n", e.num_lins, e.num_cols, e.sizeU, e.sizeR, e.numAncs);
    for (i = 0; i < e.num_lins; i++) {
      for (j = 0; j < e.num_cols; j++) {
        switch (e.grelha[j][i]) {
          case FIXO_X: c = 'X';break;
          case HINT_X:
          case SOL_X: c = 'x';break;
          case FIXO_O: c='O';break;
          case HINT_O:
          case SOL_O: c='o';break;
          case BLOQUEADA: c='#';break;
          default : c='.';
        }
        fputc(c,fp);
      }
      fputc('\n',fp);
    }
    for (i = 0; i < e.sizeU; i++) {
      pop(&x, &y, &a, &(e.undo));
      fprintf(fp,"%d %d %d ", x, y, a);
    }
    fputc('\n', fp);
    for (i = 0; i < e.sizeR; i++) {
      pop(&x, &y, &a, &(e.redo));
      fprintf(fp,"%d %d %d ", x, y, a);
    }
    fprintf(fp,"\n%d", e.id);
    fprintf(fp,"\n%d", e.validade);
    fprintf(fp,"\n%d", e.tema);
    fclose(fp);
}

void readFile(char *user, ESTADO *e)
{
    int i, j, x, y, a;
    FILE *fp;
    e->undo = NULL;
    e->redo = NULL;
    char link[60];
    char linha[20];
    sprintf(link, "/var/www/html/utilizadores/%s.txt", user);
    fp = fopen(link, "r+");
    if (fp != NULL) {
      if (fscanf(fp,"%d %d %d %d %d", &(e->num_lins), &(e->num_cols), &(e->sizeU), &(e->sizeR), &(e->numAncs)) == 5) {
        for (i = 0; i < e->num_lins; i++)
            if (fscanf(fp, "%s", linha) == 1)
              for(j = 0; j < e->num_cols; j++)
                  switch (linha[j]) {
                    case 'X': e->grelha[j][i] = FIXO_X;
                                                break;
                    case 'x': e->grelha[j][i] = SOL_X;
                                                break;
                    case 'O': e->grelha[j][i] = FIXO_O;
                                                break;
                    case 'o': e->grelha[j][i] = SOL_O;
                                                break;
                    case '#': e->grelha[j][i] = BLOQUEADA;
                                                break;
                    default : e->grelha[j][i] = VAZIA;
                  }
        for(i = 0; i < e->sizeU; i++)
          if (fscanf(fp, "%d %d %d ", &x, &y, &a) == 3)
            addEnd(x, y, a, &(e->undo));
        for(i = 0; i < e->sizeR; i++)
          if (fscanf(fp, "%d %d %d", &x, &y, &a) == 3)
            addEnd(x, y, a, &(e->redo));
        if (fscanf(fp, "%d", &(e->id)) == 1)
            if (fscanf(fp, "%d", &(e->validade)) == 1)
                if (fscanf(fp, "%d", &(e->tema)) == 1) {};
      }
    } else {
        fp = fopen(link, "w+");
        inicializar(e);
    }

    fclose(fp);
}
