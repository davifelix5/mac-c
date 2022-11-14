#include <stdio.h>
#include "swap.h"

void insertion(int arr[], int n);

int main()
{
  int v[] = {10, 1, 2, 3, 0, -1, 12, 11}, n = 8, i;
  insertion(v, n);
  for (i = 0; i < n; i++)
    printf("%d\n", v[i]);
  return 0;
}

/**
 *  O array é divido em uma parte ordenada e outra não ordenada. Então, cada elemento da parte
 * não ordenada é colocado na sua posição correta dentro da parte ordenada.
 *
 * Complexidade: O(n²)
 * Melhor caso (elemento ordenados): O(n)
 * Pior caso array na ordem reversa: O(n²)
 *
 */
void insertion(int arr[], int n)
{
  int i, j, key;
  for (i = 1; i < n; i++)
  {
    key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; j--)
      arr[j + 1] = arr[j];
    arr[j + 1] = key;
  }
}