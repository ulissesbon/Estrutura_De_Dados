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

void imprimir(struct no *l){
    struct no *aux = l;
    while(aux != NULL){
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
}


void remover(struct no **l, const char *nome){
    struct no *aux = *l;
    struct no *anterior = NULL;

    while (aux != NULL && strcmp(aux->nome, nome) != 0) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        return;
    }

    if (anterior == NULL) {
        *l = aux->prox;
    } else {
        anterior->prox = aux->prox;
    }

    free(aux);
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

    inserir_comeco(&nomes, "Ulisses");
    inserir_comeco(&nomes, "Vitoria");

    imprimir(nomes);

    remover(&nomes, "Ulisses");
    imprimir(nomes);


    frees(nomes);
    nomes = NULL;


}