#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct dados{
    int codigo;
    char nome[255];
};


struct no{
    struct dados d;
    struct no *prox;
    struct no *ant;
};

void inserir_comeco(struct no **no, struct dados d){
    struct no *aux = malloc(sizeof(struct no));
    aux->d = d;
    aux->ant = NULL;
    aux->prox = *no;

    if(*no)
        (*no)->ant = aux;
    
    *no = aux;
}

void inserir_fim(struct no **no, struct dados d){
    struct no *aux = *no;
    while(aux && aux->prox){
        aux = aux->prox;
    }

    struct no *aux2 = malloc(sizeof(struct no));
    aux2->d = d;
    aux2->ant = NULL;
    aux2->prox = NULL;

    if(aux){
        aux->prox = aux2;
        aux2->ant = aux;
    }
    else{
        aux2->ant = NULL;
        *no = aux2;    
    }
}

void listar(struct no *no){
    while(no){
        printf("Código: %d  -  Nome: %s\n", no->d.codigo, no->d.nome);
        no = no->prox;
    }
}

void liberar(struct no *no){
    struct no *temporario;
    while(no){
        temporario = no;
        no = no->prox;
        free(temporario);
    }
}




int main(){

    struct no *lista = NULL;
    struct dados aluno;

    aluno.codigo = 1;
    strcpy(aluno.nome, "Ulisses");

    inserir_comeco(&lista, aluno);

    aluno.codigo = 2;
    strcpy(aluno.nome, "Vitoria");

    inserir_fim(&lista, aluno);

    aluno.codigo = 3;
    strcpy(aluno.nome, "Pedro");
    
    inserir_fim(&lista, aluno);
    listar(lista);
    printf("\n\n");


    aluno.codigo = 4;
    strcpy(aluno.nome, "Mateus");
    
    inserir_comeco(&lista, aluno);

    aluno.codigo = 5;
    strcpy(aluno.nome, "Evelin");
    
    inserir_comeco(&lista, aluno);



    listar(lista);


    liberar(lista);


    return 0;
}