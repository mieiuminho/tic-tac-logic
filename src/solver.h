#ifndef ___SOLVER_H___
#define ___SOLVER_H___
#include "estado.h"

int fillIn (ESTADO *e,int * x,int * y);

void remHints (ESTADO *e);

void findImpossible (ESTADO * e);

#endif

