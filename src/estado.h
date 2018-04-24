#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O tamanho máximo da grelha */
#define MAX_GRID     20
#define MAX_HISTU    1601
#define MAX_HISTR    6
#define MAX_HISTA    10
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O} VALOR;
typedef enum {INICIO, SELECAO, JOGO} ID;
typedef enum {INVALIDO,IMPOSSIVEL,VALIDO} VALIDADE;
typedef enum {DEFAULT, DRACULA, MONOKAI} TEMA;

typedef struct lista
{
    int x,y;
    struct lista * next;
}* LISTA;


/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
  int id;
  int tema;
  int num_lins;
  int num_cols;
  char grelha[MAX_GRID][MAX_GRID];
  int validade;
  LISTA undo,redo;
  int sizeU,sizeR,numAncs;
} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO);

/**
\brief Função que converte uma string num estado
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *);

void readFile (char *,ESTADO *);

void writeFile (char *,ESTADO);

void inicializar (ESTADO *);

void pop (int *,int *,LISTA *);

void push (int,int,LISTA *);

void addEnd (int,int,LISTA *);

void getUserAndAction(char *,char *,char *);


#endif
