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

### Problema 3

- O terceiro probelma apresentado com pilhas foi o das N rainhas, que é conhecido desde a antiguidade.
- A resolução desse problema consiste em achar posições para que N rainhas seja dispostas, sem se atacarem, em um tabuleiro de xadrez NxN. _OBS: Nessa implemetação, apenas uma resolução será encontrada_.
- O conceito usado nesse algoritmo é o de **backtracking**, que é um tipo de algoritmo que tenta buscar resultados a partir de enumerações exaustivas mais otimizadas. Ou seja, todas as possíveis decisões são tomadas, mas, quando alguma delas leva a um resultado indesejado, o algoritmo volta para a última decisão a fim de tentar realizá-la de outro forma
- Para implementar esse tipo de algoritmo, uma pilha é extremamente adequada, já que, para **voltar à última decisão**, basta acessar o topo de uma pilha que armazene as decisões tomadas no algoritmo.

#### Lógica

```
Receba N
Inicie linha, coluna como 0
Enquanto linha < N:
  deuCerto = 0
  Enquanto coluna < N:
    Se a rainha pode ser posicionada na posição [linha][coluna]
      deuCerto = 1
  Se deuCerto, então:
    Empilhe a coluna posicionada
    Posicione a ranha
    linha++
  Caso contrário, então
    Se não há nenhuma decisão para desempilhar
      Não existe solução
    Remova a posição da última ranha
    coluna = desempilhe a última decisão
    linha--
Se houverem soluções, mostrá-las
```

**OBS:** Um problema parecido seria listar de quantas formas um _cavalo_ pode passar por todas as casas de um tabuleiro xadrez NxN com, no máximo, N² pulos.
