#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

#define MAX_BUFFER  10240

void push (int x, int y, int a, LISTA *l)
{
    LISTA new;
    new = malloc (sizeof (struct lista));
    new->x = x; new->y = y; new->a = a; new->next = *l;
    *l = new;
}

void addEnd (int x,int y,int a, LISTA *l)
{
    LISTA new, pt, ant = NULL;
    new = malloc (sizeof (struct lista));
    pt = *l;
    new->x = x; new->y = y; new->a = a; new->next = NULL;
    while (pt != NULL) {
        ant = pt;
        pt = pt->next;
    }
    if (ant != NULL) ant->next = new;
    else *l = new;
}

void pop (int *x, int *y, int *a, LISTA *l)
{
    LISTA tmp;
    tmp = *l;
    *x = tmp->x;
    *y = tmp->y;
    *a = tmp->a;
    *l = (*l)->next;
    free(tmp);
}
