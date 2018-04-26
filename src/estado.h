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
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O, HINT_X, HINT_O} VALOR;
typedef enum {INICIO, SELECAO, JOGO} ID;
typedef enum {INVALIDO,IMPOSSIVEL,VALIDO} VALIDADE;
typedef enum {DEFAULT, DRACULA, MONOKAI} TEMA;

typedef struct lista
{
    int x,y,a;
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

/**
\brief Função que lê de um ficheiro as informações relativas ao ESTADO de
um determinado usuário.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void readFile (char *user ,ESTADO *e);

/**
\brief Função que escreve num ficheiro as informações relativas ao ESTADO 
de um determinado usuário.
@param *user Nome de usuário.
@param e Estado.
*/
void writeFile (char *user ,ESTADO e);

/**
\brief Função que inicializa os parâmetros do estado.
@param *e Apontador para o ESTADO.
*/
void inicializar (ESTADO *e);

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

/**
\brief Função que adiciona um nodo, à cabeça, com as coordenadas de uma determinada jogada
e com o número de ancora correspondente, a uma determinada lista, neste caso
ou à lista do redo ou à lista do undo.
@param x coordenada no eixo dos xx.
@param y coordenada no eixo dos yy.
@param a número de ancora correspondente.
@param *l lista à qual adicionar o nodo.
*/
void push (int x, int y, int a , LISTA *l);

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
\brief Função que através da string que corresponde ao link a separa em
duas sub-strings sendo elas o utilizador e a ação a ser realizada para
"montar" o estado seguinte.
@param *link String onde está guardado todo o link por exemplo "tomás@undo".
@param *user String ode será guardado o nome do utilizador, usando o caso anterior "tomás".
@param *action String onde será guardada a ação a realizar, usando o exemplo anterior "undo".
*/
void getUserAndAction(char *link, char *user, char *action);


#endif
