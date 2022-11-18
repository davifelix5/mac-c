#include <stdio.h>
#include <stdlib.h>

#define PRETO 1
#define AZUL -1

/* Define o tipo de uma função genérica de verificação  */
typedef int (*funcaoVerifica)(int ***tab, int i, int j, int k, int n);

/* Funções para manipular o tabuleiro */
void criaTabuleiro(int ***tab, int n);
void liberaTabuleiro(int ***tab, int n);
int achaProfundidade(int ***tab, int cor, int n, int i, int j);
/* Funções para verificar vitória */
int verificaVitoria(int ***tab, int n);
int verificaLinhas(int ***tab, int i, int j, int k, int n);
int verificaColunas(int ***tab, int i, int j, int k, int n);
int verificaDiagPrincipais(int ***tab, int i, int j, int k, int n);
int verificaDiagSecundarias(int ***tab, int i, int j, int k, int n);
int verificaDiagonais(int ***tab, int n);
/* Verificar se ainda existem jogadas a serem feitas */
int temJogadas(int ***tab, int n);
/* Imprime uma campada do tabuleiro */
void imprimeCamada(int ***tab, int k, int n);

/* Escolhe a jogada ideal para o player de jogada "cor" dado o estado atual */
int escolheJogada(int ***tab, int n, int cor, int *lin, int *col);

int main()
{
  int ***tab;
  int n, c;
  int lin = 0, col = 0, k;
  int fim = 0;
  printf("n = ");
  scanf("%d", &n);

  tab = malloc(n * sizeof(int ***));

  criaTabuleiro(tab, n);
  k = escolheJogada(tab, n, PRETO, &lin, &col);
  /* tab[lin][col][k] = PRETO; */

  while (temJogadas(tab, n) && !fim)
  {
    int jogadaInvalida = 1;
    int lin_usuario, col_usuario, kUsuario;

    while (jogadaInvalida)
    {
      printf("Digite a sua jogada (lin, col): ");
      scanf("%d %d", &lin_usuario, &col_usuario);
      kUsuario = achaProfundidade(tab, AZUL, n, lin_usuario, col_usuario);

      if (kUsuario >= n)
        printf("Jogada inválida\n");
      else
        jogadaInvalida = 0;
    }

    tab[lin_usuario][col_usuario][kUsuario] = AZUL;

    k = escolheJogada(tab, n, AZUL, &lin, &col);
    /* tab[lin][col][k] = PRETO; */

    /*printf("RESULTADO LINHA: %d\n", verificaLinhas(tab, -1, -1, 0, n));
    printf("RESULTADO COLUNA: %d\n", verificaColunas(tab, -1, -1, 0, n));
    printf("RESULTADO DIAG PRINC: %d\n", verificaDiagPrincipais(tab, -1, -1, 0, n));
    printf("RESULTADO DIAG SEC: %d\n", verificaDiagSecundarias(tab, -1, -1, 0, n));
    printf("RESULTADO DIAG: %d\n", verificaDiagonais(tab, n));
    printf("VITORIA: %d\n", verificaVitoria(tab, n)); */
    for (c = 0; c < n; c++)
    {
      printf("Camada %d\n", c);
      imprimeCamada(tab, c, n);
      printf("\n");
    }

    fim = verificaVitoria(tab, n);
  }

  if (fim == AZUL)
    printf("Azul ganhou\n");
  if (fim == PRETO)
    printf("Preto ganhou\n");
  else
    printf("Empate");

  liberaTabuleiro(tab, n);

  return 0;
}

void criaTabuleiro(int ***tab, int n)
{
  int i, j, k;

  for (i = 0; i < n; i++)
  {
    tab[i] = malloc(n * sizeof(int **));
    for (j = 0; j < n; j++)
    {
      tab[i][j] = malloc(n * sizeof(int *));
      for (k = 0; k < n; k++)
        tab[i][j][k] = 0;
    }
  }
}

void liberaTabuleiro(int ***tab, int n)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      free(tab[i][j]);

  for (i = 0; i < n; i++)
    free(tab[i]);

  free(tab);
}

int achaProfundidade(int ***tab, int cor, int n, int i, int j)
{
  int k = n - 1;

  while (k >= 0 && tab[i][j][k] == 0)
    k--;

  return k + 1;
}

int escolheJogada(int ***tab, int n, int cor, int *lin, int *col)
{
  *lin = 1;
  *col = 1;
  return 1;
}

int temJogadas(int ***tab, int n)
{
  int k = n - 1, i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
      if (tab[i][j][k] == 0)
        return 1;
    }
  return 0;
}

int decideVitoria(int n, int preto, int azul)
{
  if (preto == n)
    return PRETO;
  else if (azul == n)
    return AZUL;
  return 0;
}

int verificaLinhas(int ***tab, int i, int j, int k, int n)
{
  int preto, azul, a, b, vitoria;
  for (a = 0; a < n; a++)
  {
    preto = azul = 0;
    for (b = 0; b < n; b++)
      if (k >= 0)
      {
        if (tab[a][b][k] == PRETO)
          preto++;
        else if (tab[a][b][k] == AZUL)
          azul++;
      }
      else if (i >= 0)
      {
        if (tab[i][a][b] == PRETO)
          preto++;
        else if (tab[i][a][b] == AZUL)
          azul++;
      }
      else
      {
        if (tab[a][j][b] == PRETO)
          preto++;
        else if (tab[a][j][b] == AZUL)
          azul++;
      }
    vitoria = decideVitoria(n, preto, azul);
    if (vitoria)
      return vitoria;
  }
  return 0;
}

int verificaColunas(int ***tab, int i, int j, int k, int n)
{
  int preto, azul, a, b, vitoria;
  for (a = 0; a < n; a++)
  {
    preto = azul = 0;
    for (b = 0; b < n; b++)
      if (k >= 0)
      {
        if (tab[b][a][k] == PRETO)
          preto++;
        else if (tab[b][a][k] == AZUL)
          azul++;
      }
      else if (i >= 0)
      {
        if (tab[i][b][a] == PRETO)
          preto++;
        else if (tab[i][b][a] == AZUL)
          azul++;
      }
      else
      {
        if (tab[b][j][a] == PRETO)
          preto++;
        else if (tab[b][j][a] == AZUL)
          azul++;
      }
    vitoria = decideVitoria(n, preto, azul);
    if (vitoria)
      return vitoria;
  }
  return 0;
}

int verificaDiagPrincipais(int ***tab, int i, int j, int k, int n)
{
  int preto = 0, azul = 0, a, vitoria;
  if (k >= 0)
  {
    for (a = 0; a < n; a++)
      if (tab[a][a][k] == PRETO)
        preto++;
      else if (tab[a][a][k] == AZUL)
        azul++;
  }
  else if (i >= 0)
  {
    for (a = 0; a < n; a++)
      if (tab[i][a][a] == PRETO)
        preto++;
      else if (tab[i][a][a] == AZUL)
        azul++;
  }
  else
  {
    for (a = 0; a < n; a++)
      if (tab[a][j][a] == PRETO)
        preto++;
      else if (tab[a][j][a] == AZUL)
        azul++;
  }
  vitoria = decideVitoria(n, preto, azul);
  if (vitoria)
    return vitoria;
  return 0;
}

int verificaDiagSecundarias(int ***tab, int i, int j, int k, int n)
{
  int preto = 0, azul = 0, a, b, vitoria;
  if (k >= 0)
  {
    for (a = 0, b = n - 1; a < n && b >= 0; a++, b--)
    {
      if (tab[a][b][k] == PRETO)
        preto++;
      else if (tab[a][b][k] == AZUL)
        azul++;
    }
  }
  else if (i >= 0)
  {
    for (a = 0, b = n - 1; a < n && b >= 0; a++, b--)
    {
      if (tab[i][a][b] == PRETO)
        preto++;
      else if (tab[i][a][b] == AZUL)
        azul++;
    }
  }
  else
  {
    for (a = 0, b = n - 1; a < n && b >= 0; a++, b--)
    {
      if (tab[a][j][b] == PRETO)
        preto++;
      else if (tab[a][j][b] == AZUL)
        azul++;
    }
  }
  vitoria = decideVitoria(n, preto, azul);
  if (vitoria)
    return vitoria;
  return 0;
}

int verificaDiagonais(int ***tab, int n)
{
  int i, j, k;
  int preto, azul;
  int vitoria;

  preto = azul = 0;
  for (i = 0; i < n; i++)
    if (tab[i][i][i] == PRETO)
      preto++;
    else if (tab[i][i][i] == AZUL)
      azul++;
  vitoria = decideVitoria(n, preto, azul);
  if (vitoria)
    return vitoria;

  preto = azul = 0;
  for (i = 0, j = 0, k = n - 1; i < n && j < n && k >= 0; i++, j++, k--)
    if (tab[i][j][k] == PRETO)
      preto++;
    else if (tab[i][j][k] == AZUL)
      azul++;
  vitoria = decideVitoria(n, preto, azul);
  if (vitoria)
    return vitoria;

  preto = azul = 0;
  for (i = 0, j = n - 1, k = 0; i < n && j >= 0 && k < n; i++, j--, k++)
    if (tab[i][j][k] == PRETO)
      preto++;
    else if (tab[i][j][k] == AZUL)
      azul++;
  vitoria = decideVitoria(n, preto, azul);
  if (vitoria)
    return vitoria;

  preto = azul = 0;
  for (i = 0, j = n - 1, k = n - 1; i < n && j >= 0 && k >= 0; i++, j--, k--)
    if (tab[i][j][k] == PRETO)
      preto++;
    else if (tab[i][j][k] == AZUL)
      azul++;
  vitoria = decideVitoria(n, preto, azul);
  if (vitoria)
    return vitoria;

  return 0;
}

int verificaVitoria(int ***tab, int n)
{
  int i, j, k, c;
  int resultado, diagonais;

  funcaoVerifica verificar[4] = {&verificaColunas, &verificaLinhas, &verificaDiagPrincipais, &verificaDiagSecundarias};

  for (i = 0; i < n; i++)
    for (c = 0; c < 4; c++)
    {
      resultado = verificar[c](tab, i, -1, -1, n);
      if (resultado != 0)
        return resultado;
    }
  for (j = 0; j < n; j++)
    for (c = 0; c < 4; c++)
    {
      resultado = verificar[c](tab, -1, j, -1, n);
      if (resultado != 0)
        return resultado;
    }
  for (k = 0; k < n; k++)
    for (c = 0; c < 4; c++)
    {
      resultado = verificar[c](tab, -1, -1, k, n);
      if (resultado != 0)
        return resultado;
    }

  diagonais = verificaDiagonais(tab, n);

  return diagonais;
}

void imprimeCamada(int ***tab, int k, int n)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
      printf("%4d", tab[i][j][k]);
    printf("\n");
  }
}
