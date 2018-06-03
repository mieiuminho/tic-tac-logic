#ifndef ___PUZZLES_H___
#define ___PUZZLES_H___

#define MAX_GRID     20

typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O} VALOR;
typedef enum {INVALIDO, IMPOSSIVEL, VALIDO} VALIDADE;

/**
\brief Lista ligada que armazena o histórico.
@param x Coordenada correspondente ao eixo dos xx da última posição jogada.
@param y Coordenada correspondente ao eixo dos yy da última posição jogada.
@param a Número da âncora atual.
*/
typedef struct lista {
    int x, y, a;
    struct lista *next;
} *LISTA;

/**
\brief Estrutura que armazena as caraterísitcas do tabuleiro.
*/
typedef struct puzzle {
  int num_lins, num_cols;
  int validade;
  int sizeU, sizeR, numAncs;
  LISTA undo,redo;
  char grelha[MAX_GRID][MAX_GRID];
} PUZZLE;

/**
\brief Função que adiciona um nodo, à cabeça, com as coordenadas de uma determinada jogada
e com o número de ancora correspondente, a uma determinada lista, neste caso
ou à lista do redo ou à lista do undo.
@param x coordenada no eixo dos xx.
@param y coordenada no eixo dos yy.
@param a número de ancora correspondente.
@param *l lista à qual adicionar o nodo.
*/
void push (int x, int y, int a, LISTA *l);

/**
\brief Função que adiciona um nodo, no final, com as coordenadas de uma determinada jogada
e com o número de ancora correspondente, a uma determinada lista, neste caso
ou à lista do redo ou à lista do undo.
@param x coordenada no eixo dos xx.
@param y coordenada no eixo dos yy.
@param a número de ancora correspondente.
@param *l lista à qual adicionar o nodo.
*/
void addEnd (int x, int y, int a, LISTA *l);

/**
\brief Função que retira um nodo, à cabeça, sendo que também guarda as
coordenadas da jogada do primeiro nodo da lista
e número de ancora correspondente, a uma determinada lista, neste caso
ou à lista do redo ou à lista do undo.
@param *x coordenada no eixo dos xx do nodo retirado.
@param *y coordenada no eixo dos yy do nodo retirado.
@param *a número de ancora correspondente do nodo retirado.
@param *l lista à qual retirar o nodo.
*/
void pop (int *x, int *y, int *a, LISTA *l);

#endif
