#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/**
\brief O tamanho máximo da grelha
*/
#define MAX_GRID     20

/**
\brief Possibilidades para a grelha
*/
typedef enum {BLOQUEADA, FIXO_X, FIXO_O, VAZIA, SOL_X, SOL_O, HINT_X, HINT_O} VALOR;

/**
\brief Fases do jogo possiveis
*/
typedef enum {START, LOBBY, EASY, MEDIUM, HARD, GAME} ID;

/**
\brief Fases de para a validade de um Estado
*/
typedef enum {INVALIDO, IMPOSSIVEL, VALIDO} VALIDADE;

/**
\brief Temas possiveis para o jogo
*/
typedef enum {DEFAULT, DRACULA, MONOKAI} THEME;

/**
\brief Lista ligada que armazena o histórico.
@var x Coordenada correspondente ao eixo dos xx da última posição jogada.
@var y Coordenada correspondente ao eixo dos yy da última posição jogada.
@var a Número da âncora atual.
*/
typedef struct lista {
    int x, y, a;
    struct lista *next;
} *LISTA;

/**
\brief Estrutura que armazena o estado do jogo
@var id Fase do jogo
@var tema Tema atual
@var num_lins Número de linhas
@var num_cols Número de colunas
@var grelha Matriz do jogo
@var validade Inteiro que mostra a validade
@var undo Lista do undo
@var redo Lista do redo
@var sizeU Tamanho da lista undo
@var sizeR Tamanho da lista redo
@var numAncs Número de ancoras
*/
typedef struct estado {
  int id;
  int tema;
  int num_lins, num_cols;
  char grelha[MAX_GRID][MAX_GRID];
  int validade;
  LISTA undo,redo;
  int sizeU,sizeR,numAncs;
} ESTADO;

/**
\brief Função que lê de um ficheiro as informações relativas ao ESTADO de
um determinado usuário.
@param *e Apontador para o ESTADO.
@param *user Nome de usuário.
*/
void readFile (char *user, ESTADO *e);

/**
\brief Função que escreve num ficheiro as informações relativas ao ESTADO
de um determinado usuário.
@param *user Nome de usuário.
@param e Estado.
*/
void writeFile (char *user, ESTADO e);

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
