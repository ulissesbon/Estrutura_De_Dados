#include <stdio.h>
#include <stdlib.h>

/*
struct db{
    char matricula[255];
    char nome [255];
    float notas[3];
};
*/

struct no{
    int valor;
    struct no *prox;
};

struct no *buscar(struct no *lista, int valor){
    
    struct no *aux = lista;
    while(aux != NULL  &&  aux->valor != valor){
        aux = aux->prox;
    }
    return aux;
}

void listar(struct no *lista){
    struct no *aux = lista;
    while(aux != NULL){
        printf("%d\n", aux->valor);
        aux = aux->prox;
    }
}

void alterar(struct no *lista, int valor, int novo_valor){
    struct no *aux = buscar(lista, valor);
    if(aux){
        aux->valor = novo_valor;
    }
    
}


void inserir_comeco(struct no **lista, int valor){
    
    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    if(*lista == NULL){
        aux->prox = NULL;
        *lista = aux;
    }
    else{
        aux->prox = *lista;
        *lista = aux;
        aux = NULL;
    }
}


int main(){

    struct no *ls = NULL;

    inserir_comeco(&ls, 8);
    inserir_comeco(&ls, 5);
    inserir_comeco(&ls, 3);
    inserir_comeco(&ls, 10);
    inserir_comeco(&ls, 1);
    inserir_comeco(&ls, 40);
    listar(ls);
    printf("\n\n");

    alterar(ls, 40, 88);
    alterar(ls, 3, 22);
    alterar(ls, 8, 11);
    listar(ls);
    printf("\n\n");

return 0;
}