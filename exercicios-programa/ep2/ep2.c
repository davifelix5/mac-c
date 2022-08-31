#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

int preenche(char **tab, int m, int n, int quantidade_palavras);
void imprime_matriz(char **, int, int);
void ler_palavra(palavra *p);
void inserirPalavra(char **tab, int i, int j, int dir, palavra p);
void removePalavra(char **tab, int i, int j, int dir, palavra p);
int encaixar(char **tab, int m, int n, palavra p, int i, int j, int dir);

int main()
{
  char **tab;
  int m, n, inst = 1, sol;

  scanf("%d %d", &m, &n);
  while (m != 0 && n != 0)
  {
    int i, j, qtd_palavras, tipo_posicao;

    tab = malloc(m * sizeof(char *));
    for (i = 0; i < m; i++)
    {
      tab[i] = malloc(n * sizeof(char));
      for (j = 0; j < n; j++)
      {
        scanf("%d", &tipo_posicao);
        if (tipo_posicao < 0)
          tab[i][j] = '*';
        else
          tab[i][j] = '0';
      }
    }

    scanf("%d", &qtd_palavras);

    sol = preenche(tab, m, n, qtd_palavras);

    printf("Instância %d\n", inst);
    if (sol)
      imprime_matriz(tab, m, n);
    else
      printf("Não há solução\n");
    printf("\n");

    for (i = 0; i < m; i++)
      free(tab[i]);
    free(tab);

    inst++;

    scanf("%d %d", &m, &n);
  }

  return 0;
}

int preenche(char **tab, int m, int n, int quantidade_palavras)
{
  int sol = 1, k = 0;
  int i = 0, j = 0, dir = 0;
  int arm = 0;
  palavra *armazenadas = malloc(quantidade_palavras * sizeof(palavra));
  palavra *palavraAtual = malloc(sizeof(palavra));
  pilha *encaixes = cria();

  ler_palavra(palavraAtual);

  while (k < quantidade_palavras && sol)
  {
    int encaixado = 0;
    while (i < m && !encaixado)
    {
      if (j >= n)
        j = 0;
      while (j < n && !encaixado)
      {
        if (dir > 1)
          dir = 0;
        if (tab[i][j] == '0' || tab[i][j] == palavraAtual->caracteres[0])
        {
          while (dir < 2 && !encaixado)
          {
            /*  printf("Tentando %s %d %d %d\n", palavraAtual->caracteres, i, j, dir); */
            encaixado = encaixar(tab, m, n, *palavraAtual, i, j, dir);
            dir++;
          }
        }
        j++;
      }
      i++;
    }
    if (encaixado)
    {
      /* printf("%s %d %d %d\n", palavraAtual->caracteres, i - 1, j - 1, dir - 1); */
      k++;
      /* Empilha */
      item x;
      x.lin = i - 1;
      x.col = j - 1;
      x.dir = dir - 1;
      x.p = *palavraAtual;
      empilha(encaixes, x);

      /* Insere no tabuleiro */
      inserirPalavra(tab, i - 1, j - 1, dir - 1, *palavraAtual);

      /* Identifica a proxima palavra */
      if (arm == 0 && k < quantidade_palavras)
        ler_palavra(palavraAtual);
      else
      {
        *palavraAtual = armazenadas[--arm];
        /* printf("Pegando armazenada: %s\n", palavraAtual->caracteres); */
      }

      /* Reseta valores */
      i = j = dir = 0;
      /* imprime_matriz(tab, m, n); */
    }
    else if (i == m && j == n && !pilhaVazia(encaixes))
    {

      /* Desempilha */
      item ultimo = desempilha(encaixes);
      /* printf("Desempilhei!\n"); */
      k--;
      i = ultimo.lin;
      j = ultimo.col;
      dir = ultimo.dir;
      armazenadas[arm++] = *palavraAtual;
      *palavraAtual = ultimo.p;

      /* Remove do tabuleiro */
      removePalavra(tab, i, j, dir, *palavraAtual);
      /* imprime_matriz(tab, m, n); */

      /* Atualiza valores para continuar procurando */
      dir = (dir + 1) % 2;
      j++;
      if (j >= n)
      {
        i++;
        j = 0;
      }
    }
    else
      sol = 0;
  }

  free(palavraAtual);
  destroi(encaixes);
  free(armazenadas);

  return sol;
}

int encaixar(char **tab, int m, int n, palavra p, int i, int j, int dir)
{
  int formaPalavra = 1, tamanhoPercorrido = 0;
  /* Direção horizontal */
  if (dir == 0)
  {
    int col;
    if (j - 1 >= 0 && tab[i][j - 1] != '*')
      formaPalavra = 0;

    /* Percorre a direção em questão até encontrar uma
      inconsistência na palavra ou uma barreira no tabuleiro */
    tamanhoPercorrido = 0;
    for (col = j; col < n && formaPalavra && tab[i][col] != '*'; col++)
    {
      if (tab[i][col] != '0' && tab[i][col] != p.caracteres[col - j])
        formaPalavra = 0;
      tamanhoPercorrido++;
    }
  }
  /* Direção vertical (loop análogo ao primeiro) */
  else
  {
    int lin;
    if (i - 1 >= 0 && tab[i - 1][j] != '*')
      formaPalavra = 0;

    tamanhoPercorrido = 0;
    for (lin = i; lin < m && formaPalavra && tab[lin][j] != '*'; lin++)
    {
      if (tab[lin][j] != '0' && tab[lin][j] != p.caracteres[lin - i])
        formaPalavra = 0;
      tamanhoPercorrido++;
    }
  }

  /* No fim, para a palavra encaixar, a quantidade de casas percorridas
  deve ser igual ao tamanho da palavra */
  if (tamanhoPercorrido != p.tamanho)
    formaPalavra = 0;

  return formaPalavra;
}

void ler_palavra(palavra *p)
{
  int tam = 0;
  scanf("%s", p->caracteres);
  while (p->caracteres[tam] != '\0')
    tam++;
  p->tamanho = tam;
}

void inserirPalavra(char **tab, int i, int j, int dir, palavra p)
{
  int lin, col, tam;
  if (dir == 0)
  {
    lin = i;
    for (col = j, tam = 0; tam < p.tamanho; tam++, col++)
      tab[i][col] = p.caracteres[tam];
  }
  else
  {
    col = j;
    for (lin = i, tam = 0; tam < p.tamanho; tam++, lin++)
      tab[lin][j] = p.caracteres[tam];
  }
}

void removePalavra(char **tab, int i, int j, int dir, palavra p)
{
  int lin, col, tam;
  if (dir == 0)
  {
    lin = i;
    for (col = j, tam = 0; tam < p.tamanho; tam++, col++)
      tab[i][col] = '0';
  }
  else
  {
    col = j;
    for (lin = i, tam = 0; tam < p.tamanho; tam++, lin++)
      tab[lin][j] = '0';
  }
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