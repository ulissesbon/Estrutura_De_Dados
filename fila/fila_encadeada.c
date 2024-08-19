#include <stdio.h>
#include <stdlib.h>


struct fila{
    int valor;
    struct fila *prox;
};


void adicionar(struct fila **f, int valor){
    struct fila *aux = malloc(sizeof(struct fila));
    aux->valor = valor;
    aux->prox = NULL;

    if(*f){
        struct fila *atual = *f;
        while(atual->prox != NULL){
            atual = atual->prox;  
        }
        atual->prox = aux;
    }
    else
        *f = aux;
    
}

void remover(struct fila **f){
    struct fila *aux = *f;
    *f = aux->prox;

    aux = NULL;
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

void liberar(struct fila *f){
    struct fila *aux = f;
    struct fila *aux1;

    while(aux){
        aux1 = aux;
        aux = aux->prox;
        free(aux1);
    }
}

int main(){

    struct fila *fila = NULL;

    adicionar(&fila, 8);
    adicionar(&fila, 53);
    adicionar(&fila, 14);
    adicionar(&fila, 90);

    listar(fila);

    remover(&fila);
    remover(&fila);

    listar(fila);


    liberar(fila);


    return 0;
}