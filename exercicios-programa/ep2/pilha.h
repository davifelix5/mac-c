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
  int ocupada;
} posicao;

typedef struct
{
  int palavra;
  int posicao;
} item;

typedef struct
{
  item *v;
  int topo;
  int max;
} pilha;

/* Insere um elemento no topo da pilha */
void empilha(pilha *, item);
/* Retorna o elemento no topo da pilha */
item topo(pilha *);
/* Remove e retorno o elemento no topo da pilha */
item desempilha(pilha *);
/* Verifica se a pilha está ou não vazia */
int pilhaVazia(pilha *);

/* Cria uma pilha dinamicamente na memória */
pilha *cria();
/* Libera os espaços alocados para a pilha na memória */
void destroi();
/* Dobra a quantidade máxima de elementos que cabem na pilha */
void resize(pilha *);
