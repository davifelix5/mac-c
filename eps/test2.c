#include <stdio.h>
#include <stdlib.h>

int collatz_n(int n)
{
  int c = 0, fim = 0;
  long unsigned int x = n;
  while (x != 1 && !fim)
  {
    if (x == 1)
      fim = 1;
    else if (x % 2 == 0)
    {
      x /= 2;
      c++;
    }
    else if (x % 256 == 85)
    {
      c += 9;
      x = 3 * (x / 256) + 1;
    }
    else if (x % 64 == 21)
    {
      c += 7;
      x = 3 * (x / 64) + 1;
    }
    else if (x % 16 == 5)
    {
      c += 5;
      x = 3 * (x / 16) + 1;
    }
    else
    {
      x = 3 * x + 1;
      c++;
    }
  }
  return c;
}

int main(int argc, char *argv[])
{
  int i = atoi(argv[1]), f = atoi(argv[2]);
  while (i <= f)
  {
    printf("%d\n", collatz_n(i));
    i++;
  }
  return 0;
}