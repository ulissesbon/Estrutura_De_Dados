#include <stdlib.h>
#include <stdio.h>


struct pilha{
    int valor;
    struct pilha* prox;
};


void adicionar(struct pilha **pilha, int valor){
    struct pilha *aux = malloc(sizeof(pilha));
    aux->valor = valor;
    aux->prox = NULL;

    if(*pilha == NULL){
        aux->prox = NULL;
        *pilha = aux;
    }
    else{
        aux->prox = *pilha;
        *pilha = aux;
    }
}

int remover(struct pilha **pilha){
    if (*pilha == NULL){
        printf("Pilha vazia!\n");
        return -1;
    }
    else{
        struct pilha *aux = *pilha;
        *pilha = aux->prox;
        free(aux);
        return 0;
    }
}

void mostrar(struct pilha *p){
    struct pilha *aux = p;
    printf("\n[ ");
    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("]\n");
}

void pegar(struct pilha *p){

    printf("Valor do topo: %d\n", p->valor);

}


int main(){

    struct pilha *p = NULL;

    adicionar(&p, 5);
    adicionar(&p, 42);
    adicionar(&p, 92);
    adicionar(&p, 26);

    mostrar(p);
    pegar(p);
    printf("\n");

    remover(&p);
    pegar(p);

    remover(&p);
    pegar(p);

    remover(&p);
    pegar(p);

    mostrar(p);




    return 0;
}
