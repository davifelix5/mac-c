typedef struct
{
  int tamanho;         /* quantidade de caracteres na palavra */
  char caracteres[50]; /* sequência de caracteres que formam a palavra */
  int utilizada;       /* fala se a palavra já está sendo usada no tabuleiro */
} palavra;

typedef struct
{
  int lin; /* linha da posição no tabuleiro */
  int col; /* coluna da posição no tabuleiro */
  int dir; /* direção (vertical ou horizontal) daquela posição */
} posicao;

#define HORIZONTAL 0
#define VERTICAL 1

/* Executa o backtracking para preencher o tabuleiro com as palavras */
int preenche(char **tab, int m, int n, palavra *palavras, posicao *posicoes, int n_palavras, int n_pos);

/* Registra uma nova posição no vetor posições */
void adicionaPosicao(int lin, int col, int dir, int n_pos, posicao *posicoes);

/* Preenche o tabuleiro com a palabra "plv" para a posição "pos", atualizando o mapa
  que representa em quais posições da matriz existem palavras */
void inserirPalavra(char **tab, int **mapaTab, posicao pos, palavra plv);

/* Remove a palavra "plv" do tabuleiro a partir da posição "pos", mantendo aquelas letras
  que pertencem a outra palavra a partir do mapa */
void removePalavra(char **tab, int **mapaTab, posicao pos, palavra plv);

/* Verifica se a palavra "plv" pode ser encaixada na posição "pos" */
int encaixar(char **tab, int m, int n, palavra plv, posicao pos);

/* Imprime o tabuleiro */
void imprime_matriz(char **, int, int);