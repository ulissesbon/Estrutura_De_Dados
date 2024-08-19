#include <stdio.h>
#include <stdlib.h>

#define capacidade 10

struct fila{
    int fim;
    int cap;
    int *valores;
};

void init(struct fila *f){
    f->fim = -1;
    f->cap = capacidade;
    f->valores = malloc(capacidade * sizeof(int));
}

void free_struct(struct fila *f){
    free(f->valores);
}



int listar(struct fila *f){
    int i;
    for(i=0; i < f->fim + 1 ; i++){
        printf("%d\n", *(f->valores + i));
    }
}


int inserir(struct fila *f, int valor){
    if(f->fim + 1 == f->cap){
		printf("Vetor lotado!\n");
        return -1;
    }
    else{
        int i = (f->fim) + 1;
        *(f->valores + i) = valor;
        f->fim++;
        printf("Valor adicionado!\n");
    }

}

void tamanho_fila(struct fila *f){
    printf("Topo: %d\n", f->fim + 1);
}

void excluir(struct fila *f){
    if(f->fim < 0){
        printf("Não há o que excluir!\n");
        return;
    }

    int i = 0;
    while(i < f->fim){
        *(f->valores + i) = *(f->valores + i + 1);
        i++;
    }
    f->fim = f->fim - 1;
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

