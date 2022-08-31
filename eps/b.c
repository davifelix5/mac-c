#include <stdio.h>
int main()
{
  int k, j, c_mais;
  for (k = 16, j = 5, c_mais = 5; k <= 1024; j = k + j, k *= 4, c_mais += 2)
    printf("%d %d %d\n", k, j, c_mais);
  return 0;
}