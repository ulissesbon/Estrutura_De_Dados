#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct no{
    char nome[255];
    struct no *prox;
};


struct no *buscar(struct no *n, const char *nome){
    struct no *aux = n;

    while(aux && strcmp(aux->nome, nome) != 0){
        aux = aux->prox;
    }

    return aux;
}


void listar(struct no *n){
    struct no *aux = n;

    printf("[");
    while(aux){
        printf("%s", aux->nome);
        if(aux->prox != NULL){
            printf(", ");
        }
        aux = aux->prox;
    }
    printf("]\n");
}


void add_inicio(struct no **n, const char *nome){
    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
    aux->prox = NULL;

    if(*n){
        aux->prox = *n;
        *n = aux;
        return;
    }
    *n = aux;
}


void add_fim(struct no **n, const char *nome){
    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
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
    char aux[255];

    strcpy(aux, i->nome);
    strcpy(i->nome, j->nome);
    strcpy(j->nome, aux);
}


void ordenar(struct no **n){

    if(*n == NULL)
        return;

    struct no *aux_i = *n;
    while(aux_i){
        struct no *aux_j = aux_i->prox;
        while(aux_j){
            if(strcmp(aux_i->nome, aux_j->nome) > 0){
                trocar(aux_i, aux_j);
            }
            aux_j = aux_j->prox;
        }
        aux_i = aux_i->prox;
    }
}


void add_ordem(struct no **n, const char *nome){
    ordenar(n);

    struct no *aux = malloc(sizeof(struct no));
    strcpy(aux->nome, nome);
    aux->prox = NULL;

    if(*n == NULL || strcmp((*n)->nome, nome) > 0){
        add_inicio(n, nome);
        //free(aux);
        return;
    }

    struct no *atual = *n;
    while(atual->prox && strcmp((atual->prox)->nome, nome) < 0){
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

void remover_meio(struct no **n, const char *nome){
    if(*n){
        if((*n)->prox == NULL){
            free(*n);
            return;
        }

        struct no *aux = NULL;
        struct no *atual = *n;

        while(atual){
            if(strcmp(atual->nome, nome) == 0){
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
        printf("Nome %s não encontrado!\n", nome);
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

    add_fim(&no, "Ulisses");
    add_fim(&no, "Vitoria");
    add_fim(&no, "Pedro");
    add_fim(&no, "Marcelo");

    listar(no);
    
    add_inicio(&no, "Joao");
    add_inicio(&no, "Gabriel");

    listar(no);

    ordenar(&no);

    listar(no);

    add_ordem(&no, "Ajalmar");
    add_ordem(&no, "Wesley");
    add_ordem(&no, "Anderson");
    add_ordem(&no, "Nicolas");

    listar(no);

    remover_inicio(&no);
    remover_inicio(&no);
    listar(no);

    remover_fim(&no);
    remover_fim(&no);
    listar(no);

    remover_meio(&no, "Ajalmar");
    remover_meio(&no, "Nicolas");
    listar(no);



    return 0;
}