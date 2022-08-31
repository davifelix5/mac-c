#include <stdio.h>
#include <stdlib.h>

#define MAX 5000

int collatz_n(int n, int *calculados)
{
  int c = 0, fim = 0;
  long unsigned int x = n;
  while (x != 1 && !fim)
  {
    if (x < MAX && calculados[x] != 0)
    {
      c += calculados[x];
      fim = 1;
    }
    else if (x == 1)
      fim = 1;
    else if (x % 2 == 0)
    {
      x /= 2;
      c++;
    }
    else
    {
      int k, j, c_mais, atalho;
      for (k = 16, j = 5, c_mais = 5; k <= 1024; k *= 4, j += k, c_mais += 2)
        if (x % k == j)
        {
          atalho = 1;
          c += c_mais;
          x = 3 * (x / k) + 1;
        }
      if (!atalho)
      {
        x = 3 * x + 1;
        c++;
      }
    }
  }
  if (n < MAX)
  {
    calculados[n] = c;
    /*printf("calculados[%d] = %d\n", n, c);*/
  }
  return c;
}

int main(int argc, char *argv[])
{
  int i = atoi(argv[1]), f = atoi(argv[2]);
  int *calculados = malloc(MAX * sizeof(int));
  int k;
  for (k = 0; k < MAX; k++)
    calculados[k] = 0;
  while (i <= f)
  {
    printf("%d\n", collatz_n(i, calculados));
    i++;
  }
  free(calculados);
  return 0;
}