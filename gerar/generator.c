#include "generator.h"
#include "solver.h"
#include "valida.h"
#include "historico.h"
#include <stdio.h>

void geraTabuleiro (PUZZLE * board, int dif)
{
    if (dif == 1) geraEasy(board);
    else geraHard(board);
}

int contaBloqs (PUZZLE *board)
{
  int i, j,r=0;
  for (i = 0; i < board->num_lins; i++)
    for (j = 0; j < board->num_cols; j++)
        if (board->grelha[j][i]==BLOQUEADA) r++;
  return r;
}

void geraHard (PUZZLE * board)
{
    int bloqs=1;
    while (bloqs)
    {
        int x,y,i,j,f=0;
        int a = (board->num_cols * board->num_lins) / 10;
        for (i = 0; i < a; i++)
            randomBloqPlay(board);
        while (!isFull(board))
        {
            while (solver_easy(board,&x,&y));
            f = solver_hard(board);
            if (!isFull(board)&&!f) randomPlay(board);
        }
        if (contaBloqs(board)<3*a) bloqs=0;
        else 
        {
            for (i = 0; i < board->num_cols; i++)
                for (j = 0; j < board->num_lins; j++)
                    board->grelha[i][j] = VAZIA;
        } 
    }
    

}

void geraEasy (PUZZLE * board)
{
    int x,y,i;
    int a = (board->num_cols * board->num_lins) / 5;
    for (i = 0; i < a; i++)
    {
        randomBloqPlay(board);
        if (a&1) randomPlay(board);
    }
    while (!isFull(board))
    {
        while (solver_easy(board,&x,&y));
        if (!isFull(board)) randomPlay(board);
    }
}
