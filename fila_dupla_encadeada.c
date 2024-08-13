#include <stdlib.h>
#include <stdio.h>

struct fila{
    int valor;
    struct fila *anterior;
    struct fila *prox;
};

void adicionar_inicio(struct fila **f, int valor){
    struct fila *aux = malloc(sizeof(struct fila));
    aux->valor = valor;
    aux->prox = NULL;
    aux->anterior = NULL;

    if(*f){
        aux->prox = *f;
        (*f)->anterior = aux;
        *f = aux;
        return;
    }
    else
        *f = aux;
}

void adicionar_fim(struct fila **f, int valor){
    struct fila *aux = malloc(sizeof(struct fila));
    aux->valor = valor;
    aux->prox = NULL;
    aux->anterior = NULL;
    
    if(*f){
        struct fila *atual = *f;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = aux;
        aux->anterior = atual;
        return;
    }
    else
        *f = aux;
}

void remover_inicio(struct fila **f){
    struct fila *aux = *f;
    (*f) = (*f)->prox;
    (*f)->anterior = NULL;
    free(aux);
}

void listar(struct fila *f){
    struct fila *aux = f;
    printf("[ ");
    while(aux){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("]\n");
}

void liberar(struct fila **f){
    if(*f){
        struct fila *atual = *f;
        while (atual){
            struct fila *aux = atual;
            atual = atual->prox;
            free(aux);
        }
        *f = NULL;
    }
    else
        return;
}


int main(){

    struct fila *ls;

    adicionar_fim(&ls, 13);
    adicionar_fim(&ls, 8);
    adicionar_fim(&ls, 99);
    adicionar_fim(&ls, 600);

    listar(ls);

    remover_inicio(&ls);
    remover_inicio(&ls);

    listar(ls);
    
    liberar(&ls);
    listar(ls);


    return 0;
}