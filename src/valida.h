#ifndef ___VALIDA_H___
#define ___VALIDA_H___
#include "estado.h"

int isOnTab (ESTADO * e,int i,int j);

int validaPeca (ESTADO * e,int i,int j);

int isEqual (ESTADO * e,int i,int j,int x,int y);

void setSemaforo (ESTADO * e);

#endif
