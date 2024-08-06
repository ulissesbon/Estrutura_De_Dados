#include <stdio.h>
#include <stdlib.h>

#define capacidade 10

struct fila{
    int fim;
    int cap;
    int *valores;
};

void init(struct fila *p){
    p->fim = -1;
    p->cap = capacidade;
    p->valores = malloc(capacidade * sizeof(int));
}

void free_struct(struct fila *p){
    free(p->valores);
}



int listar(struct fila *p){
    int i;
    for(i=0; i < p->fim + 1 ; i++){
        printf("%d\n", *(p->valores + i));
    }
}


int inserir(struct fila *p, int valor){
    if(p->fim + 1 == p->cap){
		printf("Vetor lotado!\n");
        return -1;
    }
    else{
        int i = (p->fim) + 1;
        *(p->valores + i) = valor;
        p->fim++;
        printf("Valor adicionado!\n");
    }

}

void tamanho_fila(struct fila *p){
    printf("Topo: %d\n", p->fim + 1);
}


void excluir(struct fila *p){
    p->fim = p->fim - 1;
}


int main(){

	
    struct fila ls;
    init(&ls);
    inserir(&ls, 8);
    inserir(&ls, 12);
    inserir(&ls, 48);
    inserir(&ls, 73);


    listar(&ls);
    tamanho_fila(&ls); 

    printf("\n");
    printf("\n");
    excluir(&ls);
    excluir(&ls);
    listar(&ls);
    tamanho_fila(&ls);



    free_struct(&ls);

    return 0;
}

