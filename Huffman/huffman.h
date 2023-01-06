#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo; //forma de arvore e lista
}No;

typedef struct{
    No * inicio;
    int tam;
}Lista;

void criar_lista(Lista *lista);
void inserir_ordenado(Lista *lista, No *no);
void inicializa(unsigned int tab[]);
void preenche_frequencia(unsigned char texto[],unsigned int tab[]);
void imprime_frequencia(unsigned int tab[]);
void preecher_lista(unsigned int tab[], Lista *lista);
void imprimir_lista(Lista *lista);
No* remove_no_inicio(Lista *lista);
No* montar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int tam);
int altura_arvore(No *raiz);
char** aloca_dicionario(int colunas);
void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas);
void imprime_dicionario(char **dicionario);
#endif // HUFFMAN_H_INCLUDED
