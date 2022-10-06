#include <stdio.h>
#include "./pilha.h"

void imprime_invertido(char s[100]);

int main()
{
	char palavra[100];
	printf("Digite uma palavra: ");
	scanf("%[^\n]", palavra);
	imprime_invertido(palavra);
	return 1;
}

void imprime_invertido(char s[100])
{
	int i = 0;
	pilha *letras = cria();

	while (s[i] != '\0' || !pilhaVazia(letras))
	{
		if (s[i] == ' ' || s[i] == '\0')
		{
			while (!pilhaVazia(letras))
				printf("%c", desempilha(letras));
			printf(" ");
		}
		else
			empilha(letras, s[i]);
		i++;
	}
	printf("\n");

	destroi(letras);
}