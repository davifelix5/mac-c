#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COMPUTER 1
#define USER -1
#define MAX 10e8
#define MIN -10e8

void criaTabuleiro(int **tab, int n);
void escolheJogada(int **tab, int *i, int *j, int n);
void freeTabuleiro(int **tab, int n);
void printaTabuleiro(int **tab, int n);
int verificaVitoria(int **tab, int n, int *ganhador);
int minimax(int **tab, int profundidade, int isMax, int alpha, int beta, int n);
int temJogadas(int **tab, int n);
int modulo(int x);

int main()
{
  int n = 5;
  int **tab = malloc(n * sizeof(int *));
  int i, j;
  int i_usuario, j_usuario;
  int fim = 0;
  int ganhador = 0;

  criaTabuleiro(tab, n);

  /*escolheJogada(tab, &i, &j, n);
  tab[i][j] = COMPUTER; */
  printaTabuleiro(tab, n);

  while (ganhador == 0 && temJogadas(tab, n))
  {
    int invalida = 1;

    while (invalida && temJogadas(tab, n))
    {
      printf("Digite sua jogada (i, j): ");
      scanf("%d %d", &i_usuario, &j_usuario);
      if (i_usuario > 0 && i_usuario <= n && j_usuario > 0 && j_usuario <= n && tab[i_usuario - 1][j_usuario - 1] == 0)
        invalida = 0;
      else
        printf("Jogada inválida\n");
    }

    tab[i_usuario - 1][j_usuario - 1] = USER;
    /*printaTabuleiro(tab, n);
    printf("PONTUAÇÃO: %d\n", verificaVitoria(tab, n, NULL));

    printf("Digite (i, j) para X: ");
    scanf("%d %d", &i, &j);
    tab[i - 1][j - 1] = COMPUTER; */

    escolheJogada(tab, &i, &j, n);
    tab[i][j] = COMPUTER;
    printaTabuleiro(tab, n);

    fim = verificaVitoria(tab, n, &ganhador);
    printf("PONTUAÇÃO: %d\n", fim);
  }

  if (ganhador == COMPUTER)
    printf("X ganhou\n");
  else if (ganhador == USER)
    printf("O ganhou\n");
  else
    printf("Empate!");

  freeTabuleiro(tab, n);

  return 0;
}

void criaTabuleiro(int **tab, int n)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    tab[i] = malloc(n * sizeof(int));
    for (j = 0; j < n; j++)
      tab[i][j] = 0;
  }
}

void freeTabuleiro(int **tab, int n)
{
  int i;
  for (i = 0; i < n; i++)
    free(tab[i]);
  free(tab);
}

void printaTabuleiro(int **tab, int n)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
      if (tab[i][j] == 1)
        printf(" X ");
      else if (tab[i][j] == -1)
        printf(" O ");
      else
        printf(" - ");
    printf("\n");
  }
}

int temJogadas(int **tab, int n)
{
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (tab[i][j] == 0)
        return 1;
  return 0;
}

int vazio(int **tab, int n)
{
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (tab[i][j] != 0)
        return 0;
  return 1;
}

int minimax(int **tab, int profundidade, int isMax, int alpha, int beta, int n)
{
  int evaluate = verificaVitoria(tab, n, NULL);

  if (modulo(evaluate) == 100 * n || profundidade == 0)
    return evaluate;

  if (!temJogadas(tab, n))
    return 0;

  if (isMax)
  {
    int best = MIN, i, j, value;
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        if (tab[i][j] == 0)
        {
          tab[i][j] = COMPUTER;
          value = minimax(tab, profundidade - 1, !isMax, alpha, beta, n);
          if (value > best)
            best = value;
          if (best > alpha)
            alpha = best;
          tab[i][j] = 0;

          if (beta <= alpha)
            break;
        }
      if (beta <= alpha)
        break;
    }
    return best;
  }
  else
  {
    int best = MAX, i, j, value;
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        if (tab[i][j] == 0)
        {
          tab[i][j] = USER;
          value = minimax(tab, profundidade - 1, !isMax, alpha, beta, n);
          if (value < best)
            best = value;
          if (best < beta)
            beta = best;
          tab[i][j] = 0;

          if (beta <= alpha)
            break;
        }
      if (beta <= alpha)
        break;
    }
    return best;
  }
}

void escolheJogada(int **tab, int *i, int *j, int n)
{
  /* Busca pela jogada do maximizer que leva a um maior valor alcançado pelo minimizer */
  int lin, col, best = MIN, value;
  if (vazio(tab, n))
  {
    *i = 0;
    *j = 0;
    return;
  }
  for (lin = 0; lin < n; lin++)
    for (col = 0; col < n; col++)
      if (tab[lin][col] == 0)
      {
        tab[lin][col] = COMPUTER;
        value = minimax(tab, 5, 0, MIN, MAX, n);
        tab[lin][col] = 0;
        if (value > best)
        {
          *i = lin;
          *j = col;
          best = value;
        }
      }
}

int modulo(int n)
{
  if (n >= 0)
    return n;
  return -n;
}

int pontuar(int p1, int p2, int n, int *ganhador)
{
  int points;
  if (p1 == n)
  {
    if (ganhador != NULL)
      *ganhador = COMPUTER;
    points = 100 * n;
  }
  else if (p2 == n)
  {
    if (ganhador != NULL)
      *ganhador = USER;
    points = 100 * n;
  }
  else if (p1 == 0)
    points = -10 * n;
  else if (p2 == 0)
    points = 10 * n;
  else
    points = 0;
  return points;
}

int linhaPreenchida(int **tab, int i, int n, int *ganhador)
{
  int p1 = 0, p2 = 0, j;
  for (j = 0; j < n; j++)
  {
    if (tab[i][j] == COMPUTER)
      p1++;
    else if (tab[i][j] == USER)
      p2++;
  }
  return pontuar(p1, p2, n, ganhador);
}

int colunaPreenchida(int **tab, int j, int n, int *ganhador)
{
  int i, p1 = 0, p2 = 0;
  for (i = 0; i < n; i++)
  {
    if (tab[i][j] == COMPUTER)
      p1++;
    else if (tab[i][j] == USER)
      p2++;
  }
  return pontuar(p1, p2, n, ganhador);
}

int diagPrincipalPreenchida(int **tab, int n, int *ganhador)
{
  int i, p1 = 0, p2 = 0;
  for (i = 0; i < n; i++)
  {
    if (tab[i][i] == COMPUTER)
      p1++;
    else if (tab[i][i] == USER)
      p2++;
  }
  return pontuar(p1, p2, n, ganhador);
}

int diagSecundariaPreenchida(int **tab, int n, int *ganhador)
{
  int i, j, p1 = 0, p2 = 0;
  for (i = 0, j = n - 1; i < n && j >= 0; i++, j--)
  {
    if (tab[i][j] == COMPUTER)
      p1++;
    else if (tab[i][j] == USER)
      p2++;
  }
  return pontuar(p1, p2, n, ganhador);
}

int verificaVitoria(int **tab, int n, int *ganhador)
{
  int i, j;
  int pontosTotais = 0;
  int pontuacao;

  for (i = 0; i < n; i++)
  {
    pontuacao = linhaPreenchida(tab, i, n, ganhador);
    pontosTotais += pontuacao;
  }

  for (j = 0; j < n; j++)
  {
    pontuacao = colunaPreenchida(tab, j, n, ganhador);
    pontosTotais += pontuacao;
  }

  pontuacao = diagPrincipalPreenchida(tab, n, ganhador);
  pontosTotais += pontuacao;

  pontuacao = diagSecundariaPreenchida(tab, n, ganhador);
  pontosTotais += pontuacao;

  return pontosTotais;
}
