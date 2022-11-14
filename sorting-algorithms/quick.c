#include <stdio.h>
#include "swap.h"

int partition(int arr[], int e, int d);
void quicksort(int v[], int e, int d);

int main()
{
  int v[] = {10, 80, 30, 90, 40, 50, 70}, i, n = 7;
  quicksort(v, 0, n);
  for (i = 0; i < n; i++)
    printf("%d\n", v[i]);
  return 0;
}

int partition(int arr[], int e, int d)
{
  int i = e - 1, j, p = arr[d - 1];
  p = arr[d - 1];

  for (j = e; j < d; j++)
    if (arr[j] <= p)
      swap(&arr[++i], &arr[j]);

  return i;
}

/**
 *  Divide o array de forma que o último delemento (pivô) esteja na sua posição correta
 * em relação à ordenação. Em seguida, repete, recursivamente, o mesmo processo para a
 * parte do array antes e a parte do array depois desse elemento.
 *
 * Complexidade média: O(nlg(n))
 * Melhor caso: O(nlg(n))
 * Pior caso: O(n²) (muito raro)
 *
 */
void quicksort(int v[], int e, int d)
{
  if (e < d - 1)
  {
    int m = partition(v, e, d);
    quicksort(v, 0, m);
    quicksort(v, m + 1, d);
  }
}