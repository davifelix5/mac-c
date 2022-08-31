#include <stdlib.h>
#include "pilha.h"

p_stack makeStack()
{
  p_stack stack = malloc(sizeof(stack));
  stack->v = malloc(15 * sizeof(item));
  stack->max = 5;
  stack->top = 0;
  return stack;
}

void freeStack(p_stack p)
{
  free(p->v);
  free(p);
}

void push(p_stack p, item value)
{
  if (p->top == p->max)
    resize(p);
  p->v[p->top++] = value;
}

item peek(p_stack p)
{
  if (!empty(p))
    return p->v[p->top - 1];
}

item pop(p_stack p)
{
  if (!empty(p))
    return p->v[--p->top];
}

int empty(p_stack p)
{
  return p->top == 0;
}

void resize(p_stack p)
{
  int i;
  item *new_v = malloc(2 * p->max * sizeof(item));
  p->max *= 2;
  for (i = 0; i < p->top; i++)
    new_v[i] = p->v[i];
  free(p->v);
  p->v = new_v;
}
