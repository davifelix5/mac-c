#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ep3.h"

int main()
{
  no *arvorePalavras = NULL;
  cel **frequencias;

  int maxFreq = 0, i;
  int *inputs, n, qtdPalavras = 0, palavrasDiferentes = 0;
  char plvValida[LEN], plv[LEN];

  /* Quantidade de inputs */
  scanf("%d", &n);

  inputs = malloc(n * sizeof(int));

  for (i = 0; i < n; i++)
    scanf("%d", &inputs[i]);

  while (scanf("%s", plv) == 1)
  {
    limpaPalavra(plv, plvValida);
    qtdPalavras++;
    palavrasDiferentes++;
    arvorePalavras = atualizaArvore(arvorePalavras, plvValida, &maxFreq, &palavrasDiferentes);
  }

  frequencias = malloc((maxFreq + 1) * sizeof(cel *));
  for (i = 0; i <= maxFreq; i++)
    frequencias[i] = NULL;

  preencheVetor(arvorePalavras, frequencias);

  printf("-- DIAGNÓSTICO DA EXECUÇÃO --\n");
  printf("Altura da árvore: %d\n", altura(arvorePalavras));
  printf("Quantidade total de palavras: %d\n", qtdPalavras);
  printf("Quantidade de palavras na árvore: %d\n", palavrasDiferentes);
  printf("Frequência máxima %d\n\n", maxFreq);

  printf("-- RESPOSTAS --\n");
  for (i = 0; i < n; i++)
  {
    int freq = inputs[i];
    printf("Frequência %d: \n", freq);

    if (freq > maxFreq || frequencias[freq] == NULL)
      printf("Não há palavras com essa frequência\n");
    else
      imprimeLista(frequencias[freq]);

    printf("\n");
  }

  liberaArvore(arvorePalavras);

  for (i = 0; i <= maxFreq; i++)
    liberaLista(frequencias[i]);
  free(frequencias);

  free(inputs);

  return 0;
}

void preencheVetor(no *raiz, cel **frequencias)
{
  if (raiz != NULL)
  {
    preencheVetor(raiz->dir, frequencias);
    frequencias[raiz->freq] = insereNoComeco(frequencias[raiz->freq], raiz);
    preencheVetor(raiz->esq, frequencias);
  }
}

no *atualizaArvore(no *raiz, char plv[LEN], int *maxFreq, int *qtdPalavras)
{
  if (raiz == NULL)
  {
    raiz = malloc(sizeof(no));
    raiz->esq = raiz->dir = NULL;
    raiz->freq = 1;
    copiaPalavra(raiz->plv, plv);
  }
  else if (comparaPalavra(plv, raiz->plv) < 0)
    raiz->esq = atualizaArvore(raiz->esq, plv, maxFreq, qtdPalavras);
  else if (comparaPalavra(plv, raiz->plv) > 0)
    raiz->dir = atualizaArvore(raiz->dir, plv, maxFreq, qtdPalavras);
  else
  {
    (*qtdPalavras)--;
    raiz->freq += 1;
  }

  if (raiz->freq > *maxFreq)
    *maxFreq = raiz->freq;

  return raiz;
}

void liberaArvore(no *raiz)
{
  if (raiz != NULL)
  {
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    free(raiz);
  }
}

int altura(no *raiz)
{
  int hdir, hesq;
  if (raiz == NULL)
    return -1;

  hdir = altura(raiz->dir);
  hesq = altura(raiz->esq);

  if (hdir > hesq)
    return 1 + hdir;
  return 1 + hesq;
}

cel *insereNoComeco(cel *inicio, no *no_plv)
{
  cel *nova = malloc(sizeof(cel));
  nova->prox = inicio;
  nova->no_palavra = no_plv;
  return nova;
}

void imprimeLista(cel *inicio)
{
  if (inicio != NULL)
  {
    printf("%s\n", inicio->no_palavra->plv);
    imprimeLista(inicio->prox);
  }
}

void liberaLista(cel *inicio)
{
  if (inicio != NULL)
  {
    liberaLista(inicio->prox);
    free(inicio);
  }
}

void copiaPalavra(char *destino, char *plv)
{
  int i;

  for (i = 0; plv[i] != '\0'; i++)
    destino[i] = lower(plv[i]);

  destino[i] = '\0';
}

int comparaPalavra(char *plv1, char *plv2)
{
  int i;

  for (i = 0; plv1[i] != '\0' && plv2[i] != '\0'; i++)
  {
    if (lower(plv1[i]) < lower(plv2[i]))
      return -1;
    else if (lower(plv1[i]) > lower(plv2[i]))
      return 1;
  }

  if (plv2[i] != '\0')
    return -1;

  return plv1[i] != '\0';
}

void limpaPalavra(char *plv, char *plvValida)
{
  int i, j;

  for (i = 0, j = 0; plv[i] != '\0'; i++)
    if ((lower(plv[i]) >= 'a' && lower(plv[i] <= 'z')) || plv[i] == '-')
      plvValida[j++] = plv[i];

  plvValida[j] = '\0';
}

char lower(char c)
{
  if (c >= 'A' && c <= 'Z')
    c = 'a' + (c - 'A');
  return c;
}
