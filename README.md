# Algoritmos em C

Esses códigos exploram conceitos relacionados à construção de **algoritmos eficientes** escritos de forma mais **legível** e **elegante** possível.

Também referem-se a **estruturas de dados** como _pilhas_, havendo sua implementação na linguagem C e a **resolução de diversos problemas** propostos que utilizam essas estruturas de dados.

## Pilhas
- A primeira estrutura de dados explorada foram as **pilhas**. Nelas, os primeiros elementos a serem adicionados são os primeiros a saírem, o que, em inglês, é classificado como _Last In, First Out_, ou seja, _LIFO_.
- As pilhas contam com 3 principais operações:
  - Ver o topo da pilha (top): retorna o elemenro que está no topo da pilha;
  - Desempilhar (pop): desempilha e retorna o último elemento da pilha;
  - Empilhar (push): adiciona um elemento no topo da pilha;
  - Vazia (isEmpty): verifica se a pilha está vazia.
  
### Problema 1
- Dada uma sequência de `(`, `)`, `[`, `]`, `{` e `}`, verificar se essa sequência é ou não válida.
- Uma sequência válida seria aquelas em que todos os caracteres que são abertos têm o caracter de fechamento correspondente na posição correta.
- `[{()()}]` é válida e `[{(})]` é inválida.
#### Lógica
```
Para cada elemento da string:
  Se o elemento for um caracter de abertura, então:
    Empilhe o caractere
  Se o carcatere for de fechamento e ele corresponde ao topo da pilha, então:
    Desempilhe
Se a pilha estiver vazia, então:
  A sequência é válida
Senão:
  A sequência é inválida
```

### Problema 2
- Dada a uma operação em notação convencional, ou seja, os operadores entre os operandos (notação infixa), determinar a notação pós-fixa, ou seja, operadores depois dos operandos, que correspondente a essa mesma operação.
- A operação na notação infixa, apesar de ser mais intuitiva, exige o conhecimento sobre precedência dos operadores. Já na notação pós-fixa, as operações já aparecem na ordem em que devem ser feitas.
- Exemplos:
  - `A-B*C` corresponde a `ABC*-`;
  - `(A+B*C)/(D*E-C)+F` corresponde à `ABC*+DE*C-/F+`.
#### Lógica
```
Para cada caractere da string:
 Se for um operando, então:
    Imprima operando
 Senão, se for '(':
    Empilha o caractere
 Senão, se for ')':
    Se a pilha estiver vazia:
      A operação é inválida, para o programa
    Enquanto topo da pilha não for '(':
      Desempilhe e imprima o topo da pilha
    Desempilha
 Senão, se for outro operador (+, -, *, /), então:
    Enquanto a pilha não está vazia ou o topo da pilha tem mais prioridade que o caractere atual:
      Desempilhe e imprima o topo da pilha
    Empilhe o operando
 Enquanto a pilha não estiver vazia:
   Desempilhe e imprima
```
