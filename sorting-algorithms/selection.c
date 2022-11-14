#include <stdio.h>
#include "swap.h"

void selection(int arr[], int n);

int main()
{
  int v[] = {10, 2, 8, 0, -1, 20, 11}, i;
  selection(v, 7);
  for (i = 0; i < 7; i++)
    printf("%d\n", v[i]);
  return 0;
}

/**
 *  Se encontrar um valor menor do que o atual, troca esses valores
 *  Complexidade: O(n²)
 *  Quantidade de trocas: O(n)
 *  Memória extra: O(1)
 *
 */
void selection(int arr[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
  {
    int min_id = i;
    for (j = i + 1; j < n; j++)
      if (arr[j] < arr[min_id])
        min_id = j;

    if (min_id != i)
      swap(&arr[i], &arr[min_id]);
    /* Invariante: os primeiros i + 1 elementos estão ordenados */
  }
}
