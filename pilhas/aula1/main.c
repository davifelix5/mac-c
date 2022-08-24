#include <stdio.h>
#include "pilha.h"

/* Verifica se o caractere passado representa uma abertura */
int abre(char);
/* Verifica se o caractere passado representa um fechamento */
int fecha(char);
/* Verifica se o caractere fecha corresponde ao fechamento do caractere abre */
int casa(char abre, char fecha);
/* Verifica se, dada uma sequencia de (, [, {, ), ], }, essa sequência é ou não válida  */
int bemFormada(char *);

int main()
{
  char s[100];
  printf("Digite uma string: ");
  scanf("%[^\n]", s);
  if (bemFormada(s))
    printf("A sequência é bem formada\n");
  else
    printf("A sequência não é bem formada\n");

  return 0;
}

int bemFormada(char *s)
{
  int i, bemformada = 1;
  p_stack stack = makeStack();
  for (i = 0; s[i] && bemformada; i++)
  {
    if (abre(s[i]))
      push(stack, s[i]);
    else if (fecha(s[i]))
    {
      if (empty(stack) || !casa(peek(stack), s[i]))
        bemformada = 0;
      else
        pop(stack);
    }
  }

  if (!empty(stack))
    bemformada = 0;

  freeStack(stack);

  return bemformada;
}

int abre(item c)
{
  return c == '(' || c == '[' || c == '{';
}

int fecha(item c)
{
  return c == ')' || c == ']' || c == '}';
}

int casa(item abre, item fecha)
{
  if ((abre == '(' && fecha == ')') ||
      (abre == '[' && fecha == ']') ||
      (abre == '{' && fecha == '}'))
    return 1;
  return 0;
}
