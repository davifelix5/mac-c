#include <stdio.h>
#include "swap.h"

void bubble(int arr[], int n);
void bubbleAviso(int arr[], int n);

int main()
{
  int v[] = {1, 2, 3, 4, 5, 6, 7, 8}, n = 8, i;
  bubble(v, n);
  for (i = 0; i < n; i++)
    printf("%d\n", v[i]);
  return 0;
}

/**
 * Bubble sort sem verificação: troca de posição quando elementos adjacentes estão em posições
 * erradas na sequência. Depois de n iterações, o vetor estará ordenado.
 *
 * Complexidade, comparações para pior e melhor caso: O(n²)
 *
 */
void bubble(int arr[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
  /* Invariante: os últimos i + 1 elementos estão ordenados */
}

/**
 * Bubble sort com verificação: troca de posição quando elementos adjacentes estão em posições
 * erradas na sequência. As iterações continuam até n vezes ou até não haver mais nenhuma troca.
 *
 * Complexidade, comparações (pior caso): O(n²)
 * Melhor caso (vetor ordenado): O(n)
 *
 */
void bubbleAviso(int arr[], int n)
{
  int trocou = 1;
  int i, j;
  for (i = 0; i < n - 1 && trocou; i++)
  {
    trocou = 0;
    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
      {
        trocou = 1;
        swap(&arr[j], &arr[j + 1]);
      }
  }
}