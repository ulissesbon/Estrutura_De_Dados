#include <stdio.h>
#include <stdlib.h>

typedef struct no_a{
    int valor;
    struct no_a *esq, *dir;
} noa;

typedef struct no_l{
    struct no_a *enoa;
    struct no_l *prox;
} nol;


void inserir_comeco_lista(nol **l, noa *a){

    if(a == NULL)
        return;

    nol *aux = malloc(sizeof(nol));
    aux->enoa = a;
    aux->prox = NULL;

    if(*l){
        aux->prox = *l;
        *l = aux;
        return;
    }

    *l = aux;

}

void inserir_final_lista(nol **l, noa *a){

    if(a == NULL)
        return;

    nol *aux = malloc(sizeof(nol));
    aux->enoa = a;
    aux->prox = NULL;

    if(*l){
        nol *atual = *l;
        while(atual->prox != NULL){
            atual = atual->prox;  
        }
        atual->prox = aux;
    }
    else
        *l = aux;
}


noa *inserir(noa *raiz, int valor){
    if(raiz == NULL){
        noa *aux = malloc(sizeof(noa));
        aux->valor = valor;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    }
    if(raiz->valor > valor){
       raiz->esq = inserir(raiz->esq, valor);
    }
    else if(raiz->valor < valor){
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

noa *remover(noa *raiz, int valor){
    if(raiz == NULL)
        return NULL;
    if(valor > raiz->valor){
        raiz->dir = remover(raiz->dir, valor);
        return raiz;
    }
    if(valor < raiz->valor){
        raiz->esq = remover(raiz->esq, valor);
        return raiz;
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        return NULL;
    }
    else if(raiz->esq != NULL && raiz->dir != NULL){
        noa *p_aux = raiz;
        noa *aux = raiz->esq;
        while(aux->dir != NULL){
            p_aux = aux;
            aux = aux->dir;
        }
        if(p_aux != raiz){
            p_aux->dir = aux->esq;
            aux->esq = raiz->esq;
        }
        aux->dir = raiz->dir;
        free(raiz);
        return aux;
    }

    else{
        noa *aux = (raiz->dir != NULL ? raiz->dir : raiz->esq);
        free(raiz);
        return aux;
    }
}


noa *buscar(noa *raiz, int valor){
    if(raiz == NULL)
        return NULL;
    if(valor > raiz->valor){
        return buscar(raiz->dir, valor);
    }
    if(valor < raiz->valor){
        return buscar(raiz->esq, valor);
    }
    return raiz;
}

nol *remove_comeco(nol **l){
    if(*l){
        nol *aux = *l;
        *l = (*l)->prox;
        return aux;
    }
    return *l;
}

void busca_largura(noa *raiz){
    if(raiz == NULL)
        return;

    nol *borda = NULL;
    inserir_final_lista(&borda, raiz);
    
    while(borda){
        nol *aux = remove_comeco(&borda);

        printf("%d\t", aux->enoa->valor);

        inserir_final_lista(&borda, aux->enoa->esq);
        inserir_final_lista(&borda, aux->enoa->dir);
        free(aux);
    }
}

void busca_profundidade(noa *raiz){
    if(raiz){
        nol *borda = NULL;
        inserir_comeco_lista(&borda, raiz);

        while(borda){
            nol *aux = remove_comeco(&borda);

            printf("%d\t", aux->enoa->valor);

            inserir_comeco_lista(&borda, aux->enoa->dir);
            inserir_comeco_lista(&borda, aux->enoa->esq);
        }
    }   
}


void em_ordem(noa *raiz){
    if(raiz == NULL)
        return;
    em_ordem(raiz->esq);
    printf("%d\t", raiz->valor);
    em_ordem(raiz->dir);
}

void pre_ordem(noa *raiz){
    if(raiz == NULL)
        return;
    printf("%d\t", raiz->valor);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
}

void pos_ordem(noa *raiz){
    if(raiz == NULL)
        return;
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d\t", raiz->valor);
}



int main(){

    noa *raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 80);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 90);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 23);
    raiz = inserir(raiz, 27);
    raiz = inserir(raiz, 85);
    raiz = inserir(raiz, 99);

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

    noa *aux = buscar(raiz, 23);
    printf("\nvalor: %d\n", aux->valor);

return 0;
}