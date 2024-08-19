#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct no{
    int valor;
    struct no *ant;
    struct no *prox;
};


void listar(struct no *n){
    struct no *aux = n;
    printf("[");
    while(aux){
        printf("%d", aux->valor);
        if(aux->prox){
            printf(", ");
        }
        aux = aux->prox;
    }
    printf("]\n");
}

void add_inicio(struct no **n, int valor){
    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    aux->ant = NULL;
    aux->prox = NULL;

    if(*n){
        aux->prox = *n;
        (*n)->ant = aux;
        *n = aux;
        return;
    }
    *n = aux;
}


void add_fim(struct no **n, int valor){
    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    aux->ant = NULL;
    aux->prox = NULL;

    if(*n){
        struct no *atual = *n;
        while(atual->prox){
            atual = atual->prox;
        }
        atual->prox = aux;
        aux->ant = atual;
        return;
    }
    *n = aux;
}

void trocar(struct no *i, struct no *j){
    int aux = i->valor;
    i->valor = j->valor;
    j->valor = aux;
}

void ordernar(struct no **n){
    if(*n == NULL)
        return;

    struct no *aux_i = *n;
    while(aux_i){
        struct no *aux_j = aux_i->prox;
        while(aux_j){
            if(aux_i->valor > aux_j->valor)
                trocar(aux_i, aux_j);
            aux_j = aux_j->prox;
        }
        aux_i = aux_i->prox;
    }
}

void add_ordem(struct no **n, int valor){
    struct no *aux = malloc(sizeof(struct no));
    aux->valor = valor;
    aux->ant = NULL;
    aux->prox = NULL;

    if(*n){
        ordernar(n);
        
        if((*n)->valor > valor){
            add_inicio(n, valor);
            free(aux);
            return;
        }

        struct no *atual = *n;
        while(atual->prox && (atual->prox)->valor < valor) {
            atual = atual->prox;
        }

        if(atual->prox != NULL){
            (atual->prox)->ant = aux;
            aux->prox = atual->prox;
            atual->prox = aux;
            aux->ant = atual;
            return;
        }

        atual->prox = aux;
        aux->ant = atual;

        return;
    }
    *n = aux;
}

void remover_inicio(struct no **n){
    if(*n){
        struct no *aux = *n;
        *n = aux->prox;
        (*n)->ant = NULL;
        free(aux);
        return;
    }
    return;
}

void remover_fim(struct no **n){
    if(*n){
        struct no *aux = *n;
        while(aux->prox){
            aux = aux->prox;
        }
        struct no *atual = aux->ant;
        atual->prox = NULL;
        free(aux);
        return;
    }
    return;
}

void remover_meio(struct no **n, int valor){
    struct no *aux = *n;
    struct no *atual = NULL;
    while(aux){
        if(aux->valor == valor){
            atual = aux;
            break;
        }
        aux = aux->prox;
    }

    if(atual){
        if(atual == *n){
            remover_inicio(n);
            return;
        }

        if(atual->prox == NULL){
            remover_fim(n);
            return;
        }

        aux = atual->ant;
        aux->prox = atual->prox;
        (aux->prox)->ant = aux;
        free(atual);
        return;
    }

    printf("Valor não encontrado!\n");
    return;
}

void liberar(struct no *n){
    struct no *aux = n;
    while(aux){
        aux = aux->prox;
        free(aux->ant);
    }
}



int main(){

    struct no *no = NULL;

    add_ordem(&no, 2);
    add_ordem(&no, 1);
    add_ordem(&no, 6);
    add_ordem(&no, 3);

    listar(no);

    add_inicio(&no, 42);
    add_inicio(&no, 1999);
    add_inicio(&no, 8);
    add_inicio(&no, 13);

    listar(no);

    add_fim(&no, 69);
    add_fim(&no, 420);
    add_fim(&no, 11001);

    listar(no);

    ordernar(&no);

    listar(no);

    add_ordem(&no, 10);
    add_ordem(&no, 100);
    add_ordem(&no, 1000);

    listar(no);

    remover_fim(&no);
    remover_fim(&no);
    listar(no);

    remover_inicio(&no);
    remover_inicio(&no);
    listar(no);

    remover_meio(&no, 100);
    remover_meio(&no, 142);
    remover_meio(&no, 42);
    listar(no);




    return 0;
}