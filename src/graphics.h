#ifndef ___GRAPHICS_H___
#define ___GRAPHICS_H___
#include "estado.h"
#define ECRA_X 1904
#define ECRA_Y 938
#define DTAB 800
#define MUDA_SEGUINTE(I,J,E) E.grelha[I][J] = (E.grelha[I][J]==5) ? 3 : ((E.grelha[I][J])+1)
#define MAX_BUFFER  10240

void abrirLink (ESTADO e);

void getScaleFactor(int * sf, ESTADO e);

void calculaCentroPeca (ESTADO e,int sf,int * fx,int * fy);

void butaoProxEstadoJog (ESTADO e,int i,int j,int sf,char * s);

void drawBloq (ESTADO e,int i,int j,int sf,char * s);

void drawPeca (int i,int j,ESTADO e,int sf);

#endif