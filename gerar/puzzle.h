#ifndef ___PUZZLES_H___
#define ___PUZZLES_H___

#define MAX_GRID     20

typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O} VALOR;
typedef enum {INVALIDO, IMPOSSIVEL, VALIDO} VALIDADE;

typedef struct lista {
    int x, y, a;
    struct lista *next;
} *LISTA;

typedef struct puzzle {
  int num_lins, num_cols;
  int validade;
  int sizeU, sizeR, numAncs;
  LISTA undo,redo;
  char grelha[MAX_GRID][MAX_GRID];
} PUZZLE;

void push (int x, int y, int a, LISTA *l);

void addEnd (int x, int y, int a, LISTA *l);

void pop (int *x, int *y, int *a, LISTA *l);

#endif
