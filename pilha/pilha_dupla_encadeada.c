#include <stdlib.h>
#include <stdio.h>

struct pilha{
    int valor;
    struct pilha *anterior;
    struct pilha *prox;
};

void adicionar_fim(struct pilha **p, int valor){
    struct pilha *aux = malloc(sizeof(struct pilha));
    aux->anterior = NULL;
    aux->prox = NULL;
    aux->valor = valor;

    if(*p){
        struct pilha *atual = *p;
        while(atual->prox){
            atual = atual->prox;
        }
        atual->prox = aux;
        aux->anterior = atual;
    }
    else
        *p = aux;
}

void remover_fim(struct pilha **p){
    struct pilha *atual = *p;
    while(atual->prox){
        atual = atual->prox;
    }
    struct pilha *aux = atual->anterior;
    aux->prox = NULL;
    free(atual);
}

void remover_meio(struct pilha **p, int valor){
    struct pilha *aux = *p;
    while(aux->prox){
        if(aux->valor == valor)
            break;
        aux = aux->prox;
    }
    if(aux == NULL){
        printf("Valor não encontrado!\n");
        return;
    }
    (aux->anterior)->prox = aux->prox;
    (aux->prox)->anterior = aux->anterior;
    free(aux);
    
}


void listar(struct pilha *p){
    struct pilha *atual = p;
    printf("[ ");
    while(atual){
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("]\n");
}

void liberar(struct pilha **p){
    if(*p){
        struct pilha *atual = *p;
        while(atual){
            struct pilha *aux = atual;
            atual = atual->prox;
            free(aux);
        }
        *p = NULL;
    }
    else
        return;
}

int main(){

    struct pilha *pp;

    adicionar_fim(&pp, 13);
    adicionar_fim(&pp, 8);
    adicionar_fim(&pp, 99);
    adicionar_fim(&pp, 1999);

    listar(pp);

    remover_meio(&pp, 99);

    listar(pp);

    liberar(&pp);
    listar(pp);

    return 0;
}