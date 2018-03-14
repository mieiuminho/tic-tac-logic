#ifndef ___HISTORICO_H___
#define ___HISTORICO_H___
#include "estado.h"

void preparaHistorico(ESTADO * e,int iH);

void adicionaHistorico(ESTADO * e,JOGADA j,int iH);

void retiraHistorico(ESTADO * e,int iH);

void fazUndo(ESTADO * e);

void fazRedo(ESTADO * e);


#endif