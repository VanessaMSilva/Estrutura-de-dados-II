#include "huffman.h"
#include<string.h>
#define TAM 256
//Tabela de frequencia

//Inicializar a tabela com zero
void inicializa(unsigned int tab[]){
    int i;
    for(i=0;i<TAM; i++){
        tab[i] = 0;
    }
}

//Preenche a tabela de frequencia
void preenche_frequencia(unsigned char texto[],unsigned int tab[]){
    int i = 0;
    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}

//Imprime a frequencia de caracteres
void imprime_frequencia(unsigned int tab[]){
    int i;
    printf("-----TABELA DE FREQUENCIA------\n");
    for(i=0; i<TAM; i++){
        if(tab[i]>0)
            printf("\t%d = %u = %c\n", i, tab[i],i);
    }
}

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;
    //A lista esta vazia
    if(lista->inicio==NULL){
        lista->inicio = no;
    }else if(no->frequencia < lista->inicio->frequencia){ // tem frequencia menor que outro no da lista
        no->proximo = lista->inicio;
        lista->inicio = no;
    }else{
        aux = lista->inicio;
        while(aux->proximo != NULL && aux->proximo->frequencia<= no->frequencia){
                aux = aux->proximo;
        }
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tam++;
}


void preecher_lista(unsigned int tab[], Lista *lista){
    int i;
    No *novo;

    for(i=0; i<TAM; i++){
        if(tab[i]>0){
            novo = malloc(sizeof(No));
            if(novo){
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            }else{
                printf("\tERRO ao alocar memoria em preencher lista");
                break;
            }

        }
    }
}

void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;
    printf("\n\t---------LISTA ORDENADA: tamanho: %d-----------------\n",lista->tam);
    while(aux){
        printf("\tCaracter: %d Frequencia: %d\n",aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

No* remove_no_inicio(Lista *lista){
    No *aux = NULL;
    if(lista->inicio!= NULL){
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }
    return aux;
}

//Montar arvore

No* montar_arvore(Lista *lista){
    No* primeiro, *segundo, *novo;

    while(lista->tam > 1){
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if(novo){
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        }else{
            printf("\nERRO ao alocar memoria em montar arvore");
            break;
        }
    }
    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam){

    if(raiz->esq == NULL && raiz->dir == NULL){
        printf("\tFolha: %c\tAltura: %d\n", raiz->caracter,tam);
    }else{
        imprimir_arvore(raiz->esq, tam+1);
        imprimir_arvore(raiz->dir, tam+1);
    }
}

int altura_arvore(No *raiz){
    int esq, dir;

    if(raiz == NULL){
        return -1;
    }else{
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;
        if(esq>dir)
            return esq;
        else
            return dir;
    }
}

char** aloca_dicionario(int colunas){
    char **dicionario;

    dicionario = malloc(sizeof(char*) * TAM);
    for(int i=0;i<TAM; i++){
        dicionario[i] = calloc(colunas, sizeof(char));
    }
    return dicionario;
}

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];

    if(raiz->dir == NULL && raiz->esq==NULL){
        strcpy(dicionario[raiz->caracter],caminho);
    }else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda,"0");
        strcat(direita,"1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void imprime_dicionario(char **dicionario){
    int i;
    printf("\n\t----------DICIONARIO:-------------\n");
    for(i=0;i<TAM;i++){
        if(strlen(dicionario[i]) > 0)
            printf("\t%3d: %s\n",i,dicionario[i]);
    }
}




