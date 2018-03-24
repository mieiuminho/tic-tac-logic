#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O tamanho máximo da grelha */
#define MAX_GRID		20
#define MAX_HISTU    10
#define MAX_HISTR    10
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O} VALOR;

/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
  char num_lins;
  char num_cols;
  char grelha[MAX_GRID][MAX_GRID];
  short int undo[MAX_HISTU];
  short int redo[MAX_HISTR];
  short int spU;
  short int spR;
} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif
