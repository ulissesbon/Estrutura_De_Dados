#include <stdio.h>
#include <stdlib.h>// codigo para arvores em si

struct noa {
int valor;
struct noa *esq;
struct noa *dir;
};

typedef struct noa noa;

// inserção// tem 2 casos a avaliar// 1o - quando o nó é nulo// 2o - quando não é nulo// versão com retorno do nó
noa *a_inserir_rr(noa *raiz, int valor)
{
    if(raiz == NULL)
    {
    noa *aux = malloc(sizeof(noa));
    aux->valor = valor;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
    }

    if(valor > raiz->valor)
    raiz->dir = a_inserir_rr(raiz->dir, valor);
    else if(valor < raiz->valor)
    raiz->esq = a_inserir_rr(raiz->esq, valor);
    else{
    // se quisesse inserir um valor já existente, mas não é o caso, pois a chave já existe 
    }
    return raiz;
}

// funcao sem retorno,usando ponteiro para ponteiro 
void a_inserir_pp(noa **raiz, int valor)
{
    if( *raiz == NULL)
    {
    noa *aux = malloc(sizeof(noa));
    aux->valor = valor;
    aux->esq = NULL;
    aux->dir = NULL;
    *raiz = aux;
    return;
    }

    noa *r = *raiz;
    if(valor > r->valor)
        a_inserir_pp(&(r->dir), valor);

    else if(valor < r->valor)
        a_inserir_pp(&(r->esq), valor);

    else{
    // se quisesse inserir um valor já existente, mas não é o caso, pois a chave já existe }
    }
}

noa *a_buscar(noa *raiz, int valor)
{
    // se não tá na árvore 
    if(raiz == NULL)
        return NULL;

    // se tem que andar na árvore 
    if(valor > raiz->valor){
        raiz->dir = a_buscar(raiz->dir, valor);
        return raiz;
    } 
    else if(valor < raiz->valor){
        raiz->esq = a_buscar(raiz->esq, valor);
        return raiz;
    }
    return raiz;
}

// a remoção deve considerar 3 casos// 1o - nós sem filhos (ou seja, folhas)// 2o - nós com apenas um filho// 3o - nós com dois filhos  
noa *a_remover(noa *raiz, int valor)
{
    // se não tá na árvore 
    if(raiz == NULL)
        return NULL;

    // se tem que andar na árvore 
    if(valor > raiz->valor){
        raiz->dir = a_remover(raiz->dir, valor);
        return raiz;
    } 
    else if(valor < raiz->valor){
        raiz->esq = a_remover(raiz->esq, valor);
        return raiz;
    }

// se chegou até aqui então é porque // achou o nó a a_remover // temos 3 casos de remoção 
    if(raiz->esq == NULL && raiz->dir == NULL) // nó sem filhos 
    {
        free(raiz);
        return NULL;
    } 
    else if(raiz->esq != NULL && raiz->dir != NULL){ // nó com 2 filhos 
        noa *p_aux = raiz;
        noa *aux = raiz->esq;

        while (aux->dir != NULL) {
            p_aux = aux;
            aux = aux->dir;
        }
        
    // aux é nó anterior a r na ordem e-r-d // p_aux é o pai de aux 
        if (p_aux != raiz) {
            p_aux->dir = aux->esq;
            aux->esq = raiz->esq;
        }
        aux->dir = raiz->dir;
        free (raiz);
        return aux;

    } 

    else { // nó com apenas um filho 
        noa *aux = (raiz->dir != NULL ? raiz->dir : raiz->esq);
        free(raiz);
        return aux;
    }

}



void a_pre_ordem(noa *raiz)
{
    if(raiz == NULL)
    return;
    printf("%d ", raiz->valor);
    a_pre_ordem(raiz->esq);
    a_pre_ordem(raiz->dir);
}


void a_em_ordem(noa *raiz)
{
    if(raiz == NULL)
    return;
    a_em_ordem(raiz->esq);
    printf("%d ", raiz->valor);
    a_em_ordem(raiz->dir);
}

void a_pos_ordem(noa *raiz)
{
    if(raiz == NULL)
    return;
    a_pos_ordem(raiz->esq);
    a_pos_ordem(raiz->dir);
    printf("%d ", raiz->valor);
}

void busca_largura(noa *raiz);
void busca_profundidade(noa *raiz);

int main() {

noa *raiz = NULL;


raiz = a_inserir_rr(raiz, 50);
raiz = a_inserir_rr(raiz, 25);
raiz = a_inserir_rr(raiz, 80);
raiz = a_inserir_rr(raiz, 20);
raiz = a_inserir_rr(raiz, 30);
raiz = a_inserir_rr(raiz, 60);
raiz = a_inserir_rr(raiz, 90);
raiz = a_inserir_rr(raiz, 10);
raiz = a_inserir_rr(raiz, 23);
raiz = a_inserir_rr(raiz, 27);
raiz = a_inserir_rr(raiz, 85);
raiz = a_inserir_rr(raiz, 99);

printf("\nem largura:\n");
busca_largura(raiz);
printf("\nem profundidade:\n");

busca_profundidade(raiz);

/* raiz = a_remover(raiz, 50); 
printf("pre-ordem: "); 
a_pre_ordem(raiz); 
printf("\n"); 
printf("em-ordem: "); 
a_em_ordem(raiz); 
printf("\n"); 
printf("pos-ordem: "); 
a_pos_ordem(raiz); 
printf("\n"); /* 
inserir_pp(&raiz,50); 
inserir_pp(&raiz,85); 
inserir_pp(&raiz,105); 
inserir_pp(&raiz,70); 
inserir_pp(&raiz,200); 
a_inserir_pp(&raiz,200); */ 
return 0;
}



// codigo para uma lista a ser usada em busca na arvore
struct nol {
    struct noa *enoa; // endereço do nó da arvore 
    struct nol *prox;
};

typedef struct nol nol;

void l_inserir_comeco(struct nol **l, noa *enoa)
{
    if(enoa == NULL)
        return;

    if(*l == NULL){
        struct nol *aux = malloc(sizeof(struct nol));
        aux->enoa = enoa;
        aux->prox = NULL;
        *l = aux;
    } else {
        struct nol *aux = malloc(sizeof(struct nol));
        aux->enoa = enoa;
        aux->prox = *l;
        *l = aux;
    }
}

struct nol *l_buscar(const struct nol *lista, noa *enoa)
{
    struct nol *aux = lista;
    while(aux != NULL && aux->enoa != enoa){
        aux = aux->prox;
    }
    return aux;
}

void l_alterar(struct nol *lista, noa *enoa, noa *novo_enoa)
{
    struct nol *no = l_buscar(lista, enoa);
    if(no){
        no->enoa = novo_enoa;
    }
}

struct nol *l_pega_no_anterior(struct nol *lista, struct nol *no)
{
    struct nol *aux = lista;
    while(aux != NULL && aux->prox != no){
        aux = aux->prox;
    }
    return aux;
}

void l_inserir_final(struct nol **l, noa *enoa)
{
    if(enoa == NULL)
        return;

    struct nol *aux = malloc(sizeof(struct nol));
    aux->enoa = enoa;
    aux->prox = NULL;

    if(*l == NULL){
        *l = aux;
        return;
    }
    struct nol *ant = l_pega_no_anterior(*l, NULL);
    ant->prox = aux;
}


int l_remover(struct nol **lista, noa *enoa)
{
    struct nol *aux = l_buscar(*lista, enoa);
    if(*lista == NULL || aux == NULL)
        return -1; // não há o que remover 
    
    if(aux == *lista){ // está nol começo 
        *lista = (*lista)->prox;
        free(aux);
    } 
    else if (aux->prox == NULL){ // está nol fim 
        struct nol *ant = l_pega_no_anterior(*lista, aux);
        ant->prox = NULL;
        free(aux);
    } 
    else { // está nol meio 
        struct nol *ant = l_pega_no_anterior(*lista, aux);
        ant->prox = aux->prox;
        free(aux);
    }
    return 0;
}

nol *l_remover_comeco(struct nol **lista)
{
    if(*lista == NULL)
        return NULL; // não há o que remover 
    nol *aux = *lista;
    *lista = (*lista)->prox;
    return aux;
}


void l_listar(const struct nol *lista)
{
    struct nol *aux = lista;
    printf("[ ");
    while(aux != NULL){
        printf("%p", aux->enoa);

        if(aux->prox != NULL)
            printf(", ");
        aux = aux->prox;
    }
    printf("]\n");
}

int l_vazia(nol *lista){
    if(lista == NULL)
        return 1;

    else 
        return 0;
}


void busca_largura(noa *raiz)
{
    if(raiz == NULL)
    return;

    nol *borda = NULL; // borda é uma lista com os nós a serem visitados(mostrados) 
    l_inserir_final(&borda, raiz); // insere a raiz 
    while(!l_vazia(borda))
    {
        nol *l_cabeca = l_remover_comeco(&borda);
    // visito tal elemento (imprimir por exemplo) 
        noa *no_arvore = l_cabeca->enoa;
        printf("%d ", no_arvore->valor);
    // pego os filhos e coloco na borda no fim da lista 
        l_inserir_final(&borda, no_arvore->esq); // nao insiro se ponteiro enoa for NULL, ajustei codigo 
        l_inserir_final(&borda, no_arvore->dir); // nao insiro se ponteiro enoa for NULL, ajustei codigo 
        free(l_cabeca);
    }
}

void busca_profundidade(noa *raiz)
{
    if(raiz == NULL)
        return;

    nol *borda = NULL; // borda é uma lista com os nós a serem visitados(mostrados) 
    l_inserir_final(&borda, raiz); // insere a raiz 
    while(!l_vazia(borda))
    {
        nol *l_cabeca = l_remover_comeco(&borda);
        // visito tal elemento (imprimir por exemplo)   
        noa *no_arvore = l_cabeca->enoa;
        printf("%d ", no_arvore->valor);
        // pego os filhos e coloco na borda no fim da lista 
        l_inserir_comeco(&borda, no_arvore->dir); // nao insiro se ponteiro enoa for NULL, ajustei codigo 
        l_inserir_comeco(&borda, no_arvore->esq); // nao insiro se ponteiro enoa for NULL, ajustei codigo 
        free(l_cabeca);
    }
}