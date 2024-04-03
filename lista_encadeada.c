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

void inserir_fim(struct no **lista, int valor){

    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    if (*lista == NULL){
        aux->prox = NULL;
        *lista = aux;
    }
    else{
        struct no *aux2 = *lista;
        while(aux2->prox != NULL){
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
    }
}

void inserir_ordem(struct no **lista, int valor){

    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;

    if(*lista == NULL){
        aux->prox = NULL;
        *lista = aux;
        return;
    }

    if((*lista)->prox == NULL){
        if((*lista)->valor <= valor){
            (*lista)->prox = aux;
            aux->prox = NULL;
            return;
        }
        else{
            aux->prox = *lista;
            *lista = aux;
            return;
            
        }
    }

    if((*lista)->valor > valor){
        aux->prox = *lista;
        *lista = aux;
        return;
    }

    struct no *anterior = *lista;
    struct no *atual = (*lista)->prox;
    
    while(atual->valor < valor && atual->prox !=NULL){
        anterior = anterior->prox;
        atual = atual->prox;
    }
    if(atual->prox == NULL){
        aux->prox = NULL;
        atual->prox = aux;
    }
    else{
        aux->prox = atual;
        anterior->prox = aux;
    }

}


int main(){

    struct no *ls = NULL;

    inserir_ordem(&ls, 15);
    inserir_ordem(&ls, 10);
    inserir_ordem(&ls, 1226524);
    inserir_ordem(&ls, 1565);
    inserir_ordem(&ls, 140);
    inserir_ordem(&ls, 7);
    
    listar(ls);


return 0;
}