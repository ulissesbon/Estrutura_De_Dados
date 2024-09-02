#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *esq, *dir;
} no;

no *inserir(no *raiz, int valor){
    if(raiz == NULL){
        no *aux = malloc(sizeof(no));
        aux->valor = valor;
    }
}