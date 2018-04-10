#ifndef ___HISTORICO_H___
#define ___HISTORICO_H___
#include "estado.h"

void push(ESTADO * e,int jog,int iH);

void pop(ESTADO * e,int iH);

void fazUndo(ESTADO * e);

void fazRedo(ESTADO * e);

void toPair (int * x,int * y,int num);

int fromPair (int x,int y);

void saveAncora(ESTADO * e,short int x);

void deleteAncora(ESTADO * e);

void fazAncoras(ESTADO * e);

void fUndoA (ESTADO * e,short int aux [],int n);

void rUndoA (ESTADO * e,short int aux [],int n);

#endif