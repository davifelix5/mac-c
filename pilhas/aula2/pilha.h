#define ERR -1

typedef char item;

typedef struct
{
  item *v;
  int top;
  int max;
} stack;

typedef stack *p_stack;

/* Insere um elemento no topo da pilha */
void push(p_stack, item);
/* Retorna o elemento no topo da pilha */
item peek(p_stack);
/* Remove e retorno o elemento no topo da pilha */
item pop(p_stack);
/* Verifica se a pilha está ou não vazia */
int empty(p_stack);

/* Cria uma pilha dinamicamente na memória */
p_stack makeStack();
/* Libera os espaços alocados para a pilha na memória */
void freeStack();
/* Dobra a quantidade máxima de elementos que cabem na pilha */
void resize(p_stack);