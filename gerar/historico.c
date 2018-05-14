#include "historico.h"

void marcaAncora (PUZZLE *board)
{
    board->numAncs++;
}

void voltaAncora (PUZZLE *board)
{
    int x, y, a;

    if (board->numAncs > 0 && board->sizeU > 0) {
        do
            fazUndo (board, &x, &y, &a);
        while (board->sizeU && a == board->numAncs);

        if (board->sizeU)
            fazRedo (board,&x,&y,&a);
        board->numAncs--;
    }
}

void fazRedo(PUZZLE *board,int *x,int *y,int *a)
{
    pop (x, y, a, &(board->redo));

    if (board->grelha[*x][*y] == SOL_O)
      board->grelha[*x][*y] = VAZIA;
    else board->grelha[(*x)][(*y)]++;

    push (*x, *y, *a, &(board->undo));

    if(*a > board->numAncs) board->numAncs++;

    board->sizeR--;
    board->sizeU++;
}

void fazUndo(PUZZLE *board, int *x, int *y, int *a)
{
    pop(x, y, a, &(board->undo));

    switch (board->grelha[*x][*y]) {
        case SOL_O:
        case SOL_X: board->grelha[*x][*y] = VAZIA;
                    break;
        case VAZIA: board->grelha[*x][*y] = SOL_O;
                    break;
    }

    push(*x, *y, *a, &(board->redo));

    board->sizeR++;
    board->sizeU--;
}
