#include <stdio.h>
#include <stdlib.h>

void mergesort(int arr[], int ini, int fim);
void merge(int arr[], int ini, int meio, int fim);

int main()
{
  int v[] = {38, 27, 43, 3, 9, 82, 10}, n = 7, i;
  mergesort(v, 0, n);
  for (i = 0; i < n; i++)
    printf("%d\n", v[i]);
  return 0;
}

/**
 *  Divive o array principal na metade, gerando dois subarrays, até que haja 1 ou 0 elementos
 * nos subarrays. Então, combina esses subarrays de forma que os elementos menores de cada
 * um deles apareçam primeiro.
 *
 * Complexidade: O(nlg(n))
 * Espaço adicional: O(n)
 *
 * @param arr
 * @param ini
 * @param fim
 */
void mergesort(int arr[], int ini, int fim)
{
  if (ini < fim - 1)
  {
    int meio = (ini + fim - 1) / 2;
    mergesort(arr, ini, meio + 1);
    mergesort(arr, meio + 1, fim);
    merge(arr, ini, meio, fim);
  }
}

void merge(int arr[], int ini, int meio, int fim)
{
  int i = ini, j = meio + 1, k;
  int *aux = malloc((fim - ini) * sizeof(int));

  for (k = 0; i <= meio && j < fim; k++)
    if (arr[i] < arr[j])
      aux[k] = arr[i++];
    else
      aux[k] = arr[j++];

  while (i <= meio)
    aux[k++] = arr[i++];

  while (j < fim)
    aux[k++] = arr[j++];

  for (i = ini, k = 0; i < fim; i++, k++)
    arr[i] = aux[k];

  free(aux);
}