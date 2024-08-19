#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct no{
    int valor;
    struct no *prox;
};


struct no *buscar(struct no *n, int valor){
    struct no *aux = n;

    while(aux && aux->valor != valor){
        aux = aux->prox;
    }

    return aux;
}


void listar(struct no *n){
    struct no *aux = n;

    printf("[");
    while(aux){
        printf("%d", aux->valor);
        if(aux->prox != NULL){
            printf(", ");
        }
        aux = aux->prox;
    }
    printf("]\n");
}


void add_inicio(struct no **n, int valor){
    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    aux->prox = NULL;

    if(*n){
        aux->prox = *n;
        *n = aux;
        return;
    }
    *n = aux;
}


void add_fim(struct no **n, int valor){
    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    aux->prox = NULL;

    if(*n){
        struct no *atual = *n;
        while(atual->prox){
            atual = atual->prox;
        }
        atual->prox = aux;
        return;
    }
    *n = aux;
}


void trocar(struct no *i, struct no *j){
    int aux = i->valor;
    i->valor = j->valor;
    j->valor = aux;
}


void ordenar(struct no **n){

    if(*n == NULL)
        return;

    struct no *aux_i = *n;
    while(aux_i){
        struct no *aux_j = aux_i->prox;
        while(aux_j){
            if(aux_i->valor > aux_j->valor){
                trocar(aux_i, aux_j);
            }
            aux_j = aux_j->prox;
        }
        aux_i = aux_i->prox;
    }
}


void add_ordem(struct no **n, int valor){
    ordenar(n);

    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    aux->prox = NULL;

    if(*n == NULL || (*n)->valor > valor){
        add_inicio(n, valor);
        //free(aux);
        return;
    }

    struct no *atual = *n;
    while(atual->prox && (atual->prox)->valor < valor){
        atual = atual->prox;
    }
    aux->prox = atual->prox;
    atual->prox = aux;

}

void remover_inicio(struct no **n){
    if(*n){
        struct no *aux = *n;
        *n = aux->prox;
        free(aux);
        return;
    }

    return;
}

void remover_fim(struct no **n){
    if(*n){
        struct no *aux = *n;
        if(aux->prox == NULL){
            free(aux);
            return;
        }

        while((aux->prox)->prox){
            aux = aux->prox;
        }
        free(aux->prox);
        aux->prox = NULL;
        return;
    }
    return;
}

void remover_meio(struct no **n, int valor){
    if(*n){
        if((*n)->prox == NULL){
            free(*n);
            return;
        }

        struct no *aux = NULL;
        struct no *atual = *n;

        while(atual){
            if(atual->valor == valor){
                aux = atual;
                break;
            }
            atual = atual->prox;
        }

        if(aux){
            atual = *n;
            while(atual->prox != aux){
                atual = atual->prox;
            }
            atual->prox = aux->prox;
            free(aux);
            return;
        }
        printf("Valor não encontrado!\n");
        return;
    }
    return;
}


void liberar(struct no *n){
    struct no *aux = n;
    struct no *atual = NULL;

    while(aux){
        atual = aux;
        aux = aux->prox;
        free(atual);
    }
}



int main(){


    struct no *no = NULL;

    add_fim(&no, 13);
    add_fim(&no, 8);
    add_fim(&no, 1999);
    add_fim(&no, 42);

    listar(no);
    
    add_inicio(&no, 3);
    add_inicio(&no, 2);

    listar(no);

    ordenar(&no);

    listar(no);

    add_ordem(&no, 1);
    add_ordem(&no, 10);
    add_ordem(&no, 100);
    add_ordem(&no, 1000);
    add_ordem(&no, 10000);

    listar(no);

    remover_inicio(&no);
    remover_inicio(&no);
    listar(no);

    remover_fim(&no);
    remover_fim(&no);
    listar(no);

    remover_meio(&no, 100);
    remover_meio(&no, 42);
    listar(no);



    return 0;
}