#include <stdio.h>
#include "pilha.h"

int prioridade(char);
void posfixa(char *);

int main()
{
  char exp[100];
  printf("Digite uma expressão: ");
  scanf("%s", exp);
  posfixa(exp);
  return 0;
}

void posfixa(char *exp)
{
  p_stack ops = makeStack();
  int i;
  char c;

  for (i = 0, c = exp[i]; exp[i]; c = exp[++i])
  {

    if (c >= 'A' && c <= 'Z')
      printf("%c", c);
    else if (c == '(')
      push(ops, c);
    else if (c == ')')
    {
      if (empty(ops))
      {
        printf("Sua expressão está inválida");
        freeStack(ops);
        return;
      }
      while (peek(ops) != '(')
        printf("%c", pop(ops));
      pop(ops);
    }
    else if (c == '+' || c == '-' || c == '/' || c == '*')
    {
      while (!empty(ops) && prioridade(peek(ops)) >= prioridade(c))
        printf("%c", pop(ops));
      push(ops, c);
    }
  }

  while (!empty(ops))
    printf("%c", pop(ops));
  printf("\n");

  freeStack(ops);
}

int prioridade(char c)
{
  if (c == '+' || c == '-')
    return 1;
  else if (c == '/' || c == '*')
    return 2;
  return 0;
}
