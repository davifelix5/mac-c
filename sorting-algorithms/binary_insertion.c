#include <stdio.h>

int binaryFind(int arr[], int x, int e, int d);
void binary_inserion(int arr[], int n);

int main()
{
  int v[] = {1, 5, 8, 2, 20, -1}, i;
  binary_inserion(v, 6);
  for (i = 0; i < 6; i++)
    printf("%d\n", v[i]);
  return 0;
}

/**
 *  Retorna a posição na qual um número x deve entrar em um array arr[e...d-1] para que ele
 * permaneça ordenado
 */
int binaryFind(int arr[], int x, int e, int d)
{
  int meio;

  if (e >= d - 1)
    return e; /* Ordenação instável */

  meio = (e + d - 1) / 2;

  if (arr[meio] == x)
    return meio + 1;

  if (x < arr[meio])
    return binaryFind(arr, x, e, meio);

  return binaryFind(arr, x, meio + 1, d);
}

/**
 *  Insertion sort no qual a posição do elemento a ser inserido na parte ordenada é encontrada
 * a partir de uma busca binária, o que diminui o tempo de busca de O(n) para O(lg(n))
 *
 */
void binary_inserion(int arr[], int n)
{
  int i;
  for (i = 1; i < n; i++)
  {
    int j = i - 1, key = arr[i], pos = binaryFind(arr, key, 0, i);

    while (j >= pos)
    {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = key;
  }
}