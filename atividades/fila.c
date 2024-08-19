#include <stdlib.h>
#include <stdio.h>

#define capacidade 10

struct lista {
    int fim;
    int capac;
    int *valores;
};


void init(struct lista *f){
    f->fim = -1;
    f->capac = capacidade;
    f->valores = malloc(capacidade * sizeof(int));
}


int add_inicio(struct lista *f, int valor){
    if(f->fim == f->capac - 1){
        printf("Fila cheia!\n");
        return -1;
    }

    f->fim++;
    int i = f->fim;
    while(i > 0){
        *(f->valores + i) = *(f->valores + i - 1);
        i--;
    }

    *(f->valores) = valor;

}






int add_fim(struct lista *f, int valor){
    if(f->fim == f->capac - 1){
        printf("Fila cheia!\n");
        return -1;
    }

    f->fim++;
    int i = f->fim;
    *(f->valores + i) = valor; 

}


void listar(struct lista *f){
    int i = 0;
    printf("[");
    while(i <= f->fim){
        printf("%d", *(f->valores + i));
        if(i < f->fim)
            printf(", ");

        i++;
    }
    printf("]\n");
}


int main(){

    struct lista *f;

    init(f);

    listar(f);

    add_fim(f, 13);
    add_fim(f, 8);
    add_fim(f, 1999);
    add_fim(f, 42);

    listar(f);


    add_inicio(f, 11111);
    add_inicio(f, 0);
    add_inicio(f, 3);
    add_inicio(f, 2);
    add_inicio(f, 1);

    listar(f);

    



    return 0;
}