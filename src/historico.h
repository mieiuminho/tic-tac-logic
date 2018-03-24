#ifndef ___HISTORICO_H___
#define ___HISTORICO_H___
#include "estado.h"

void push(ESTADO * e,int jog,int iH);

void pop(ESTADO * e,int iH);

void fazUndo(ESTADO * e);

void fazRedo(ESTADO * e);

void toPair (int * x,int * y,int num);

int fromPair (int x,int y);


#endif