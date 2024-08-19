#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no{
    char nome[255];
    struct no *prox;
};

int inserir_comeco(struct no **lista, const char *nome){
    struct no *aux = malloc(sizeof(struct no));

    if(aux == NULL){
        return -1;
    }
    strcpy(aux->nome, nome);
    aux->prox = *lista;
    *lista = aux;
}

int inserir_fim(struct no **lista, const char *nome){
    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
    aux->prox = NULL;

    
    if(aux == NULL){
        return -1;
    }
    
    if(*lista == NULL){
        *lista = aux;
        return 0;
    }
    else{
        struct no *atual = *lista;
        while(atual->prox){
            atual = atual ->prox;
        }
        atual->prox = aux;
    }
}



void imprimir(struct no *l){
    struct no *aux = l;
    while(aux != NULL){
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
}

void frees(struct no *l){
    struct no *aux = l;
    while(aux != NULL){
        struct no *ant = aux;
        aux = aux->prox;
        free(ant);
    }
}

int main(){

    struct no *nomes = NULL;

    inserir_fim(&nomes, "Ulisses");
    inserir_fim(&nomes, "Vitoria");

    imprimir(nomes);
    nomes = NULL;


    frees(nomes);


}