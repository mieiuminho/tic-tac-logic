#ifndef ___HISTORICO_H___
#define ___HISTORICO_H___
#include "estado.h"

void preparaHistorico(ESTADO * e);

void adicionaHistorico(ESTADO * e,JOGADA j);

void retiraHistorico(ESTADO * e);

void fazUndo(ESTADO * e);

void fazRedo(ESTADO * e);


#endif