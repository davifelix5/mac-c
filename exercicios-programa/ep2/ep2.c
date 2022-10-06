#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

#define HORIZONTAL 0
#define VERTICAL 1

int preenche(char **tab, int m, int n, palavra *palavras, posicao *posicoes, int n_palavras, int n_pos);
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

    sol = preenche(tab, m, n, palavras, posicoes, n_plvrs, n_pos);

    printf("Instância %d\n", inst);
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

    inst++;

    scanf("%d %d", &m, &n);
  }

  return 0;
}

int preenche(char **tab, int m, int n, palavra *palavras, posicao *posicoes, int n_palavras, int n_pos)
{
  int sol = 1, pos = 0, palv = 0;
  int **mapaTab = malloc(m * sizeof(int *)), i, j;
  pilha *encaixes = cria();

  /* Vericando se a quantidade de palavras é validas */
  if (n_palavras < n_pos)
    return 0;

  for (i = 0; i < m; i++)
  {
    mapaTab[i] = malloc(n * sizeof(int));
    for (j = 0; j < n; j++)
      mapaTab[i][j] = 0;
  }

  while (pos < n_pos && sol)
  {
    int encaixado = 0;
    while (palv < n_palavras && !encaixado)
    {
      if (!palavras[palv].utilizada)
        encaixado = encaixar(tab, m, n, palavras[palv], posicoes[pos]);
      palv++;
    }
    if (encaixado)
    {
      item x;
      /* Empilha */
      palavras[palv - 1].utilizada = 1;
      x.posicao = pos;
      x.palavra = palv - 1;

      empilha(encaixes, x);

      /* Insere no tabuleiro */
      inserirPalavra(tab, mapaTab, posicoes[pos], palavras[palv - 1]);

      /* Vai para a proxima posição */
      pos++;
      /* Reinicia as palavras */
      palv = 0;
    }
    else if (!pilhaVazia(encaixes))
    {
      /* Desempilha */
      item ultimo = desempilha(encaixes);
      pos = ultimo.posicao;
      palv = ultimo.palavra + 1;
      palavras[palv - 1].utilizada = 0;

      /* Remove do tabuleiro */
      removePalavra(tab, mapaTab, posicoes[pos], palavras[palv - 1]);
    }
    else
      sol = 0;
  }

  destroi(encaixes);

  for (i = 0; i < m; i++)
    free(mapaTab[i]);
  free(mapaTab);

  return sol;
}

int encaixar(char **tab, int m, int n, palavra plv, posicao pos)
{
  int formaPalavra = 1, tamanhoPercorrido = 0;
  if (pos.dir == HORIZONTAL)
  {
    int col;

    /* Percorre a direção em questão até encontrar uma
      inconsistência na palavra ou uma barreira no tabuleiro */
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

    /* Loop análogo ao anterior */
    tamanhoPercorrido = 0;
    for (lin = pos.lin; lin < m && formaPalavra && tab[lin][pos.col] != '*'; lin++)
    {
      if (tab[lin][pos.col] != '0' && tab[lin][pos.col] != plv.caracteres[lin - pos.lin])
        formaPalavra = 0;
      tamanhoPercorrido++;
    }
  }

  /* No fim, para a palavra encaixar, a quantidade de casas percorridas
  deve ser igual ao tamanho da palavra */
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
      /* Remove a letra apenas se não há outra palavra da qual
        ela faça parte */
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
  p.ocupada = 0;
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