#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*
  Receba n rainhas
  Declare um vetor v no qual cada índice i é uma linha e cada valor v[i] = j
é uma coluna onde está localizada uma rainha
  Inicie um contador i=0 para rainhas posicionadas

  Comece j = 0, i = 0
  Enquanto i < n
    Tente posicionar a rainha em v[k] = j para todo k de j até n
    Se der certo,
      i++; j=0
      Empilhe a decisão
    Se não der certo então,
      Se não tiver uma última decisão para desempilhar
        return 0
      Desempilhe a decisão anterior d
      i--; j = d + 1

  printa o tabuleiro
  return 1
*/

#define EMPTY -1

int nrainhas(int);
int podeMover(int *, int, int, int);
void printaTabuleiro(int *, int);

int main()
{
  int n;
  printf("Digite n: ");
  scanf("%d", &n);
  nrainhas(n);
  return 0;
}

int nrainhas(int n)
{
  int *posicoes = malloc(n * sizeof(int)), k;
  p_stack moves = makeStack();
  int i = 0, j = 0;
  int temSolucao = 1;

  for (k = 0; k < n; k++)
    posicoes[k] = EMPTY;

  while (i < n && temSolucao)
  {
    int ok = 0;

    while (j < n && !ok)
      if (podeMover(posicoes, i, j, n))
        ok = 1;
      else
        j++;

    if (ok)
    {
      push(moves, j);
      posicoes[i++] = j;
      j = 0;
    }
    else if (empty(moves))
      temSolucao = 0;
    else
    {
      posicoes[--i] = EMPTY;
      j = pop(moves) + 1;
    }
  }

  if (temSolucao)
    printaTabuleiro(posicoes, n);

  free(posicoes);
  freeStack(moves);

  return 1;
}

int podeMover(int *posicoes, int i, int j, int n)
{
  int k, l;

  for (k = 0; k < n; k++)
    if (posicoes[k] == j)
      return 0;

  for (k = 0, l = j - i; k < n; k++, l++)
    if (posicoes[k] == l && l >= 0 && l < n)
      return 0;

  for (k = 0, l = j + i; k < n; k++, l--)
    if (posicoes[k] == l && l >= 0 && l < n)
      return 0;

  return 1;
}

void printaTabuleiro(int *posicoes, int n)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
      if (posicoes[i] == j)
        printf(" X ");
      else
        printf(" - ");
    printf("\n");
  }
}