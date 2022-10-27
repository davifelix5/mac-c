/* DEFINIÇÕES E TIPOS */

#define LEN 50

typedef struct no_arvore
{
  struct no_arvore *esq;
  struct no_arvore *dir;
  char plv[LEN];
  int freq;
} no;

typedef struct cel_lista
{
  struct cel_lista *prox;
  no *no_palavra;
} cel;

/* Percorre a árvore pós-ordem e preenche o vetor de frequências  */
void preencheVetor(no *raiz, cel **frequencias);

/* ------- FUNÇÕES DE ÁRVORE ------- */

/* Atualiza as palavras e suas frequências correspondes na árvore */
no *atualizaArvore(no *raiz, char plv[LEN], int *maxFreq);

/* Libera a árvore alocada */
void liberaArvore(no *raiz);

/* Retorno a altura da árvore */
int altura(no *raiz);

/* ------- FUNÇÕES DE LISTA LIGADA------- */

/* Insere um elemento no começo da lista ligada */
cel *insereNoComeco(cel *inicio, no *no_plv);

void imprimeLista(cel *inicio);

/* Libera a memória usada na lista ligada */
void liberaLista(cel *inicio);

/* ------- FUNÇÕES DE STRING ------- */

/* Copia a palavra de um endereço da memória para outro */
void copiaPalavra(char *plv, char *destino);

/*
  Compara as palavras plv1 e plv2 em relação à ordem alfabética
    Se plv1 vem antes de plv2, retorna -1.
    Se plv2 vem antes de plv1, retorna 1.
    Se as duas palavras forem iguais, retorna 0.
*/
int comparaPalavra(char *plv1, char *plv2);

/* Devolve o caractere correspondete em letra minúscula */
char lower(char c);

/* Remove sinais de pontuação no fim da palavra  */
char *limpaPalavra(char *plv);