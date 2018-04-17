#include "solver.h"
#include "boards.h"
#include "cgi.h"
#include "estado.h"
#include "graphics.h"
#include "historico.h"
#include "menu.h"
#include "valida.h"

// Função que percorre o tabuleiro e preenche com os casos imediatos
void fillIn (ESTADO *e)
{
    int i, j, found;
    i=j=found=0;
    for(i=0;(i<e->num_lins)&&(!found);i++)
    {
        for(j=0;(j<e->num_cols)&&(!found);j++)
        {
          if(e->grelha[i][j]==VAZIA)
          {
            e->grelha[i][j]=SOL_X;
            if (!validaPeca(e,i,j))
            {
              e->grelha[i][j]=SOL_O;
              found = 1;
            }
            else if (!found)
            {
              e->grelha[i][j]=SOL_O;
              if (!validaPeca(e,i,j))
              {
                e->grelha[i][j]=SOL_X;
                found = 1;
              }
            }
            if (!found) e->grelha[i][j]=VAZIA;
          }

        }
    }
}

