#include <stdio.h>
#include "pilha.h"

/*
 * Objetivo do algoritmo:
 *
 *    Dada uma expressão matemática na notação isual (infixa),
 * determinar uma expressão equivalente na notação posfixa
 *
 * Exemplo: A*B/C-D deve retornar AB*C/D-
 *
 * /

/*
 * Lógica do algoritmo:
 *
 * Para cada caractere da string:
 *   Se for um operando, então:
 *      Imprima operando
 *   Senão, se for abre parênteses:
 *      Empilha
 *   Semão, se for ):
 *      Se a pilha estiver vazia:
 *        A operação é inválida, para o programa
 *      Enquanto topo da pilha não for (:
 *        Imprima e desempilhe o topo da pilha
 *      Desempilha
 *   Senão, se for outro operador (+, -, *, /), então:
 *      Enquanto a não está vazia ou o topo da pilha tem mais prioridade que o caractere atual:
 *        Imprima e desempilhe o topo da pilha
 *      Empilhe o operando
 *
 *  Enquanto a pilha não estiver vazia:
 *     Imprima e desempilhe o operando
 */

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
