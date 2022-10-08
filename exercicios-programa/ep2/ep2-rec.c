#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct
{
  int tamanho;
  char caracteres[50];
  int utilizada;
} palavra;

typedef struct
{
  int lin;
  int col;
  int dir;
} posicao;

#define HORIZONTAL 0
#define VERTICAL 1

int preenche(char **tab, int m, int n, palavra *palavras, posicao *posicoes, int n_palavras, int n_pos, int atual, int **mapaTab);
void adicionaPosicao(int lin, int col, int dir, int n_pos, posicao *posicoes);
void inserirPalavra(char **tab, int **mapaTab, posicao pos, palavra plv);
void removePalavra(char **tab, int **mapaTab, posicao pos, palavra plv);
int encaixar(char **tab, int m, int n, palavra plv, posicao pos);
void imprime_matriz(char **, int, int);

int main()
{
  char **tab;
  palavra *palavras;
  posicao *posicoes;
  int m, n, inst = 1, sol = 0;

  scanf("%d %d", &m, &n);
  while (m != 0 && n != 0)
  {
    int i, j, k, numero;
    int n_pos = 0, n_plvrs = 0;

    int **mapaTab = malloc(m * sizeof(int *));

    for (i = 0; i < m; i++)
    {
      mapaTab[i] = malloc(n * sizeof(int));
      for (j = 0; j < n; j++)
        mapaTab[i][j] = 0;
    }

    tab = malloc(m * sizeof(char *));
    for (i = 0; i < m; i++)
    {
      tab[i] = malloc(n * sizeof(char));
      for (j = 0; j < n; j++)
      {
        scanf("%d", &numero);
        if (numero < 0)
          tab[i][j] = '*';
        else
          tab[i][j] = '0';
      }
    }

    posicoes = malloc(m * n * sizeof(posicao));

    for (i = 0; i < m; i++)
    {
      for (j = 0; j < n; j++)
      {
        int vert, hor;

        /* Verifica se uma palavra pode ser colocada horizontal ou verticalmente
          naquela posição */
        vert = (i - 1 < 0 || tab[i - 1][j] == '*') && i + 1 < m && tab[i + 1][j] != '*';
        hor = (j - 1 < 0 || tab[i][j - 1] == '*') && j + 1 < n && tab[i][j + 1] != '*';

        if (vert && tab[i][j] != '*')
        {
          adicionaPosicao(i, j, VERTICAL, n_pos, posicoes);
          n_pos++;
        }
        if (hor && tab[i][j] != '*')
        {
          adicionaPosicao(i, j, HORIZONTAL, n_pos, posicoes);
          n_pos++;
        }
      }
    }

    scanf("%d", &n_plvrs);

    palavras = malloc(n_plvrs * sizeof(palavra));

    for (k = 0; k < n_plvrs; k++)
    {
      int tam = 1;
      palavra p;
      scanf("%s", p.caracteres);
      while (p.caracteres[tam] != '\0')
        tam++;
      p.tamanho = tam;
      p.utilizada = 0;
      palavras[k] = p;
    }

    if (n_plvrs < n_pos)
      sol = 0;
    else
      sol = preenche(tab, m, n, palavras, posicoes, n_plvrs, n_pos, 0, mapaTab);

    printf("Instânciaa %d\n", inst);
    if (sol)
      imprime_matriz(tab, m, n);
    else
      printf("Não há solução\n");
    printf("\n");

    for (i = 0; i < m; i++)
      free(tab[i]);
    free(tab);

    free(posicoes);
    free(palavras);

    for (i = 0; i < m; i++)
      free(mapaTab[i]);
    free(mapaTab);

    inst++;

    scanf("%d %d", &m, &n);
  }

  return 0;
}

int preenche(char **tab, int m, int n, palavra *palavras, posicao *posicoes, int n_palavras, int n_pos, int atual, int **mapaTab)
{
  int palv = 0;

  if (atual == n_pos)
    return 1;

  for (palv = 0; palv < n_palavras; palv++)
  {
    if (!palavras[palv].utilizada && encaixar(tab, m, n, palavras[palv], posicoes[atual]))
    {
      inserirPalavra(tab, mapaTab, posicoes[atual], palavras[palv]);
      if (!preenche(tab, m, n, palavras, posicoes, n_palavras, n_pos, atual + 1, mapaTab))
        removePalavra(tab, mapaTab, posicoes[atual], palavras[palv]);
      else
        return 1;
    }
  }
  return 0;
}

int encaixar(char **tab, int m, int n, palavra plv, posicao pos)
{
  int formaPalavra = 1, tamanhoPercorrido = 0;
  if (pos.dir == HORIZONTAL)
  {
    int col;

    tamanhoPercorrido = 0;
    for (col = pos.col; col < n && formaPalavra && tab[pos.lin][col] != '*'; col++)
    {
      if (tab[pos.lin][col] != '0' && tab[pos.lin][col] != plv.caracteres[col - pos.col])
        formaPalavra = 0;
      tamanhoPercorrido++;
    }
  }
  else
  {
    int lin;

    tamanhoPercorrido = 0;
    for (lin = pos.lin; lin < m && formaPalavra && tab[lin][pos.col] != '*'; lin++)
    {
      if (tab[lin][pos.col] != '0' && tab[lin][pos.col] != plv.caracteres[lin - pos.lin])
        formaPalavra = 0;
      tamanhoPercorrido++;
    }
  }

  if (tamanhoPercorrido != plv.tamanho)
    formaPalavra = 0;

  return formaPalavra;
}

void inserirPalavra(char **tab, int **mapa, posicao pos, palavra plv)
{
  int lin, col, tam;
  if (pos.dir == HORIZONTAL)
  {
    lin = pos.lin;
    for (col = pos.col, tam = 0; tam < plv.tamanho; tam++, col++)
    {
      mapa[pos.lin][col] += 1;
      tab[pos.lin][col] = plv.caracteres[tam];
    }
  }
  else
  {
    col = pos.col;
    for (lin = pos.lin, tam = 0; tam < plv.tamanho; tam++, lin++)
    {
      mapa[lin][pos.col] += 1;
      tab[lin][pos.col] = plv.caracteres[tam];
    }
  }
}

void removePalavra(char **tab, int **mapa, posicao pos, palavra plv)
{
  int lin, col, tam;
  if (pos.dir == HORIZONTAL)
  {
    lin = pos.lin;
    for (col = pos.col, tam = 0; tam < plv.tamanho; tam++, col++)
    {
      if (mapa[pos.lin][col] == 1)
        tab[pos.lin][col] = '0';
      mapa[pos.lin][col] -= 1;
    }
  }
  else
  {
    col = pos.col;
    for (lin = pos.lin, tam = 0; tam < plv.tamanho; tam++, lin++)
    {
      if (mapa[lin][pos.col] == 1)
        tab[lin][pos.col] = '0';
      mapa[lin][pos.col] -= 1;
    }
  }
}

void adicionaPosicao(int lin, int col, int dir, int n_pos, posicao *posicoes)
{
  posicao p;
  p.lin = lin;
  p.col = col;
  p.dir = dir;
  posicoes[n_pos] = p;
}

void imprime_matriz(char **tab, int m, int n)
{
  int i, j;
  for (i = 0; i < m; i++)
  {
    for (j = 0; j < n; j++)
      printf(" %c ", tab[i][j]);
    printf("\n");
  }
}