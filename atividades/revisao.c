#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct no{
    char nome[255];
    struct no *anterior;
    struct no *prox;
};

typedef struct no nos;

void add_fim(nos **no, const char *nome){
    nos *aux = malloc(sizeof(nos));
    strcpy(aux->nome, nome);
    aux->anterior = NULL;
    aux->prox = NULL;

    if(*no){
        nos *atual = *no;
        while(atual->prox){
            atual = atual->prox;
        }
        atual->prox = aux;
        aux->anterior = atual;
        return;
    }
    *no = aux;
}

void add_inicio(nos **no, const char *nome){
    nos *aux = malloc(sizeof(nos));
    strcpy(aux->nome, nome);
    aux->anterior = NULL;
    aux->prox = NULL;

    if(*no){
        aux->prox = *no;
        (*no)->anterior = aux;
        *no = aux;
        return;
    }
    *no = aux;
}

void add_ordem(nos **no, const char *nome){
    nos *aux = malloc(sizeof(nos));
    strcpy(aux->nome, nome);
    aux->anterior = NULL;
    aux->prox = NULL;

    if(*no == NULL){
        *no = aux;
        return;
    }

    if(strcmp((*no)->nome, aux->nome) > 0){
        add_inicio(no, nome);
        return;
    }
    
    nos *atual = *no;
    while(atual && atual->prox && strcmp((atual->prox)->nome, nome) < 0){
        atual = atual->prox;
    }
    aux->prox = atual->prox;
    aux->anterior = atual;
    atual->prox = aux;
}


void listar(nos *no){
    nos *aux = no;
    while(aux){
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
}


int main(){

    nos *nomes = NULL;

    add_ordem(&nomes, "Ulisses");
    add_ordem(&nomes, "Vitoria");
    add_ordem(&nomes, "Davi");
    add_ordem(&nomes, "Cauan");
    add_ordem(&nomes, "Ajalmar");


    listar(nomes);




    return 0;
}