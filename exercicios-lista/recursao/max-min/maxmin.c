#include <stdio.h>

int max(int *v, int n);
int min(int *v, int n);

int main()
{
  int v[6] = {2, 1, 4, 1, 8, 3};
  printf("MAX: %d\n", max(v, 6));
  printf("MIN: %d\n", min(v, 6));
  return 1;
}

int max(int *v, int n)
{
  int aux;
  if (n == 1)
    return v[0];
  aux = max(v, n - 1);
  if (aux > v[n - 1])
    return aux;
  return v[n - 1];
}

int min(int *v, int n)
{
  int aux;
  if (n == 1)
    return v[0];
  aux = min(v, n - 1);
  if (aux < v[n - 1])
    return aux;
  return v[n - 1];
}