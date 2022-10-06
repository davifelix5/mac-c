#include <stdio.h>
#include <stdlib.h>

typedef int item;

typedef struct cel
{
  item info;
  struct cel *prox;
} celula;

celula *insereNoInicio(celula *cel, item x);
celula *insereNoFim(celula *inicio, item x);
celula *removeDoInicio(celula *inicio);
celula *removeElemento(celula *inicio, item x);

celula *busca(celula *inicio, item x);
celula *buscaRecursiva(celula *inicio, item x);

void imprimeLista(celula *incio);
void imprimeListaRecursivo(celula *inicio);

int main()
{
  int x;
  celula *inicio = NULL;
  celula *encontrado;
  item buscado;

  printf("Digite os elementos da lista (zero termina): ");
  scanf("%d", &x);
  while (x != 0)
  {
    inicio = insereNoFim(inicio, x);
    scanf("%d", &x);
  }

  imprimeLista(inicio);

  printf("Digite o elemento para procurar: ");
  scanf("%d", &buscado);

  encontrado = busca(inicio, buscado);
  if (encontrado)
    printf("Elemento encontrado: %d\n", encontrado->info);
  else
    printf("Elemento não encontrado\n");
  return 0;
}

celula *insereNoInicio(celula *inicio, item x)
{
  celula *novo = malloc(sizeof(celula));
  novo->info = x;
  novo->prox = inicio;
  inicio = novo;
  return novo;
}

void imprimeLista(celula *inicio)
{
  celula *ptr = inicio;
  while (ptr != NULL)
  {
    printf(" %d ", ptr->info);
    ptr = ptr->prox;
  }
  printf("\n");
}

void imprimeListaRecursivo(celula *inicio)
{
  if (inicio != NULL)
  {
    printf(" %d ", inicio->info);
    imprimeLista(inicio->prox);
  }
  printf("\n");
}

celula *busca(celula *inicio, item x)
{
  celula *ptr = inicio;
  while (ptr != NULL && ptr->info != 8)
    ptr = ptr->prox;
  return ptr;
}

celula *buscaRecursiva(celula *inicio, item x)
{
  if (inicio == NULL || inicio->info == x)
    return inicio;
  return buscaRecursiva(inicio->prox, x);
}

celula *insereNoFim(celula *inicio, item x)
{
  celula *novo;
  if (inicio == NULL)
  {
    inicio = malloc(sizeof(celula));
    inicio->info = x;
    inicio->prox = NULL;
    return inicio;
  }
  inicio->prox = insereNoFim(inicio->prox, x);
  return inicio;
}

celula *removeDoInicio(celula *inicio)
{
  celula *aux;
  if (inicio != NULL)
  {
    aux = inicio;
    inicio = aux->prox;
    free(aux);
  }
  return inicio;
}

celula *removeElemento(celula *inicio, item x)
{
  celula *p = inicio, *ant = NULL, *aux;
  while (p != NULL && p->info != x)
  {
    p = p->prox;
    ant = p;
  }
  if (p == NULL)
    return inicio;
  if (ant != NULL)
    ant->prox = p->prox;
  else
    inicio = inicio->prox;
  free(p);
  return inicio;
}