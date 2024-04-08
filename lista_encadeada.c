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

    printf("[ ");

    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }

    printf("]\n");
}

void trocar(struct no *i, struct no *j){
    int aux = i->valor;
    i->valor = j->valor;
    j->valor = aux;
}

void ordenar(struct no *lista){
    
    struct no *aux_i = lista;
    
    while(aux_i != NULL){
        struct no *aux_j = aux_i->prox;
        while(aux_j != NULL){
            if(aux_i->valor > aux_j->valor){
                trocar(aux_i, aux_j);
            }
        aux_j = aux_j->prox;
        }
        aux_i = aux_i->prox;
    }
    

}


void alterar(struct no *lista, int valor, int novo_valor){
    struct no *aux = buscar(lista, valor);
    if(aux){
        aux->valor = novo_valor;
    }
    
}

struct no *pegar_anterior(struct no *lista, struct no *no){

    struct no *aux = lista;
    while(aux != NULL && aux->prox != no){
        aux = aux->prox;
    }
    return aux;

}

int remover(struct no **lista, int valor){
    struct no *aux = buscar(*lista, valor);
    if(*lista == NULL || aux == NULL){
        return -1;
    }
    if(aux == *lista){
        *lista = (*lista)->prox;
        free(aux);
    }
    else if(aux->prox == NULL){
        struct no *ant = pegar_anterior(*lista, aux);
        ant->prox = NULL;
        free(aux);
    }
    else{
        struct no *ant = pegar_anterior(*lista, aux);
        ant->prox = aux->prox;
        free(aux);
    }

    return 0;
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
    aux->prox = NULL;

    if (*lista == NULL){
        *lista = aux;
        return;
    }
    struct no *ant = pegar_anterior(*lista, NULL);
        ant->prox = aux;
}

void inserir_ordem(struct no **lista, int valor){

    ordenar(*lista);

    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;

    if(*lista == NULL){
        aux->prox = NULL;
        *lista = aux;
        return;
    }


    struct no *anterior = *lista;
    struct no *proximo = *lista;
    
    if(valor < (*lista)->valor){
        inserir_comeco(&(*lista), valor);
        return;
    }

    while(proximo->valor < valor && proximo->prox != NULL){
        proximo = proximo->prox;
    }
    if(proximo->prox == NULL){
        inserir_fim(&(*lista), valor);
        return;
    }
    anterior = pegar_anterior(*lista, proximo);
    anterior->prox = aux;
    aux->prox = proximo;

}


int main(){

    struct no *ls = NULL;

    inserir_ordem(&ls, 10);
    inserir_fim(&ls, 77);
    inserir_ordem(&ls, 51345);
    inserir_comeco(&ls, 37);
    inserir_ordem(&ls, 42);
    inserir_comeco(&ls, 15);
    inserir_fim(&ls, 20);
    inserir_ordem(&ls, 30);
    
    listar(ls);
    
return 0;
}