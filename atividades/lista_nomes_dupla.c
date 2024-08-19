#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct no{
    char nome[255];
    struct no *ant;
    struct no *prox;
};


void listar(struct no *n){
    struct no *aux = n;
    printf("[");
    while(aux){
        printf("%s", aux->nome);
        if(aux->prox){
            printf(", ");
        }
        aux = aux->prox;
    }
    printf("]\n");
}

void add_inicio(struct no **n, const char *nome){
    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
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


void add_fim(struct no **n, const char *nome){
    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
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
    char aux[255];
    strcpy(aux, i->nome);
    strcpy(i->nome, j->nome);
    strcpy(j->nome, aux);
}

void ordernar(struct no **n){
    if(*n == NULL)
        return;

    struct no *aux_i = *n;
    while(aux_i){
        struct no *aux_j = aux_i->prox;
        while(aux_j){
            if(strcmp(aux_i->nome, aux_j->nome) > 0)
                trocar(aux_i, aux_j);
            aux_j = aux_j->prox;
        }
        aux_i = aux_i->prox;
    }
}

void add_ordem(struct no **n, const char *nome){
    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
    aux->ant = NULL;
    aux->prox = NULL;

    if(*n){
        ordernar(n);
        
        if(strcmp((*n)->nome, nome) > 0){
            add_inicio(n, nome);
            free(aux);
            return;
        }

        struct no *atual = *n;
        while(atual->prox && strcmp((atual->prox)->nome, nome) < 0) {
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

void remover_meio(struct no **n, const char *nome){
    struct no *aux = *n;
    struct no *atual = NULL;
    while(aux){
        if(strcmp(aux->nome, nome) == 0){
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

    printf("Nome %s não encontrado!\n", nome);
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

    add_ordem(&no, "Ulisses");
    add_ordem(&no, "Vitoria");
    add_ordem(&no, "Pedro");
    add_ordem(&no, "Daniel");

    listar(no);

    add_inicio(&no, "Gabriel");
    add_inicio(&no, "Ajalmar");
    add_inicio(&no, "Carlos");
    add_inicio(&no, "Nivardo");

    listar(no);

    add_fim(&no, "Joao");
    add_fim(&no, "Marcos");
    add_fim(&no, "Victor");

    listar(no);

    ordernar(&no);

    listar(no);

    add_ordem(&no, "Matheus");
    add_ordem(&no, "Sophia");
    add_ordem(&no, "Mirela");

    listar(no);

    remover_fim(&no);
    remover_fim(&no);
    listar(no);

    remover_inicio(&no);
    remover_inicio(&no);
    listar(no);

    remover_meio(&no, "Mirela");
    remover_meio(&no, "142");
    remover_meio(&no, "Joao");
    listar(no);




    return 0;
}