#include <stdio.h>
#include <stdlib.h>

int quatroCores(int **mapa, int n, int *cores, int atual);
int corValida(int **mapa, int n, int *cores, int atual, int cor);

int main()
{
  int n, i, j;
  int *cores;
  int **mapa;
  scanf("%d", &n);

  mapa = malloc(n * sizeof(int *));
  cores = malloc(n * sizeof(int));
  for (i = 0; i < n; i++)
  {
    cores[i] = 0;
    mapa[i] = malloc(n * sizeof(int));
    for (j = 0; j < n; j++)
      scanf("%d", &mapa[i][j]);
  }

  quatroCores(mapa, n, cores, 0);

  for (i = 0; i < n; i++)
    printf("País %d: Cor %d\n", i, cores[i]);

  return 1;
}

int quatroCores(int **mapa, int n, int *cores, int atual)
{
  int cor;

  if (atual == n)
    return 1;

  for (cor = 1; cor <= 4; cor++)
  {
    if (corValida(mapa, n, cores, atual, cor))
    {
      cores[atual] = cor;
      if (!quatroCores(mapa, n, cores, atual + 1))
        cores[atual] = 0;
      else
        return 1;
    }
  }
  return 0;
}

int corValida(int **mapa, int n, int *cores, int atual, int cor)
{
  int i;
  for (i = 0; i < n; i++)
    if (mapa[atual][i] == 1 && cores[i] == cor && i != atual)
      return 0;
  return 1;
}