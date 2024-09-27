#include <stdlib.h>
#include <stdio.h>

typedef struct no_arvore {
    int valor;
    struct no_arvore *esq;
    struct no_arvore *dir;
} noa;


typedef struct no_lista{
    struct no_arvore *no_arvore;
    struct no_lista *prox;
} nol;


void inserir_final_lista(nol **l, noa *raiz){

    if(raiz == NULL)
        return;
    
    nol *aux = malloc(sizeof(nol));
    aux->no_arvore = raiz;
    aux->prox = NULL;

    if(*l){
        nol *atual = *l;
        while(atual->prox){
            atual = atual->prox;
        }
        atual->prox = aux;
        return;
    }
    *l = aux;
}

void inserir_comeco_lista(nol **l, noa *raiz){

    if(raiz == NULL)
        return;

    nol *aux = malloc(sizeof(nol));
    aux->no_arvore = raiz;
    aux->prox = NULL;

    if(*l){
        aux->prox = *l;
        *l = aux;
        return;
    }

    *l = aux;
}

nol *remove_comeco_lista(nol **l){
    if(*l){
        nol *aux = *l;
        *l = (*l)->prox;
        return aux;
    }
    return *l;
}



noa *inserir_arvore(noa *raiz, int valor){
    if(raiz == NULL){
        noa *aux = malloc(sizeof(noa));
        aux->valor = valor;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    }

    if(valor < raiz->valor){
        raiz->esq = inserir_arvore(raiz->esq, valor);
    }
    else if(valor > raiz->valor){
        raiz->dir = inserir_arvore(raiz->dir, valor);
    }
    return raiz;
}

noa *remover_arvore(noa *raiz, int valor){
    if(raiz == NULL)
        return NULL;
    
    if(valor < raiz->valor){
        raiz->esq = remover_arvore(raiz->esq, valor);
        return raiz;
    }
    else if(valor > raiz->valor){
        raiz->dir = remover_arvore(raiz->dir, valor);
        return raiz;
    }

    if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        return NULL;
    }
    else if(raiz->esq != NULL && raiz->dir != NULL){
        
        noa *p_aux = raiz;
        noa *aux = raiz->esq;

        while(aux->dir){
            p_aux = aux;
            aux = aux->dir;
        }

        if (p_aux != raiz){
            p_aux->dir = aux->esq;
            aux->esq = raiz->esq;
        }
        aux->dir = raiz->dir;
        free(raiz);
        return aux;
    }

    else{
        noa *aux = (raiz->dir != NULL? raiz->dir : raiz->esq);
        free(raiz);
        return aux;
    }
}

noa *buscar(noa *raiz, int valor){
    if(raiz == NULL)
        return NULL;
    
    if(valor < raiz->valor){
        raiz->esq = buscar(raiz->esq, valor);
        return raiz;
    }
    else if(valor > raiz->valor){
        raiz->dir = buscar(raiz->dir, valor);
        return raiz;
    }
    return raiz;;
}

void pre_ordem(noa *raiz){
    if(raiz == NULL)
        return;
    printf("%d\t", raiz->valor);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
}

void em_ordem(noa *raiz){
    if(raiz == NULL)
        return;
    em_ordem(raiz->esq);
    printf("%d\t", raiz->valor);
    em_ordem(raiz->dir);
}

void pos_ordem(noa *raiz){
    if(raiz == NULL)
        return;
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d\t", raiz->valor);
}

void busca_largura(noa *raiz){
    if(raiz == NULL)
        return;
    
    nol *borda = NULL;
    inserir_final_lista(&borda, raiz);

    while(borda){
        nol *aux = remove_comeco_lista(&borda);

        printf("%d\t", aux->no_arvore->valor);

        inserir_final_lista(&borda, aux->no_arvore->esq);
        inserir_final_lista(&borda, aux->no_arvore->dir);
        free(aux);
    }
}

void busca_profundidade(noa *raiz){
    if(raiz == NULL)
        return;
    
    nol *borda = NULL;
    inserir_comeco_lista(&borda, raiz);

    while(borda){
        nol *aux = remove_comeco_lista(&borda);

        printf("%d\t", aux->no_arvore->valor);

        inserir_comeco_lista(&borda, aux->no_arvore->dir);
        inserir_comeco_lista(&borda, aux->no_arvore->esq);
        free(aux);
    }
}

int main(){

    noa *raiz = NULL;

    raiz = inserir_arvore(raiz, 50);
    raiz = inserir_arvore(raiz, 65);
    raiz = inserir_arvore(raiz, 33);
    raiz = inserir_arvore(raiz, 10);
    raiz = inserir_arvore(raiz, 99);
    raiz = inserir_arvore(raiz, 70);
    raiz = inserir_arvore(raiz, 23);
    raiz = inserir_arvore(raiz, 23);
    raiz = inserir_arvore(raiz, 23);
    raiz = inserir_arvore(raiz, 23);


    printf("\nPré-ordem:\n");
    pre_ordem(raiz);
    printf("\n");

    printf("\nEM ordem:\n");
    em_ordem(raiz);
    printf("\n");

    printf("\nPós-ordem:\n");
    pos_ordem(raiz);

    printf("\n");
    printf("\nBusca em largura:\n");
    busca_largura(raiz);

    printf("\n");
    printf("\nBusca em profundidade:\n");
    busca_profundidade(raiz);


    raiz = remover_arvore(raiz, 50);
    raiz = remover_arvore(raiz, 23);
    raiz = remover_arvore(raiz, 99);

    printf("\n");
    busca_largura(raiz);




    return 0;
}