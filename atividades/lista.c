#include <stdlib.h>
#include <stdio.h>

#define capacidade 10

struct lista {
    int fim;
    int capac;
    int *valores;
};


void init(struct lista *l){
    l->fim = -1;
    l->capac = capacidade;
    l->valores = malloc(capacidade * sizeof(int));
}


int add_inicio(struct lista *l, int valor){
    if(l->fim == l->capac - 1){
        printf("Fila cheia!\n");
        return -1;
    }

    l->fim++;
    int i = l->fim;
    while(i > 0){
        *(l->valores + i) = *(l->valores + i - 1);
        i--;
    }

    *(l->valores) = valor;

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


int add_meio(struct lista *f, int valor, int posicao){
    if(f->fim == f->capac - 1){
        printf("Fila cheia!\n");
        return -1;
    }

    if (posicao < 0 || posicao > f->fim + 1) {
        printf("Posição inválida!\n");
        return -1;
    }

    f->fim++;
    int i = f->fim;
    while(i >= posicao){
        *(f->valores + i) = *(f->valores + i -1);
        i--;
    }

    *(f->valores + posicao) = valor;
}


int remover_inicio(struct lista *f){
    if(f->fim < 0){
        printf("Não há o que remover!\n");
        return -1;
    }

    int i = 0;
    while(i < f->fim){
        *(f->valores + i) = *(f->valores + i + 1);
    }   
    f->fim--;
}

int remover_fim(struct lista *f){
    if(f->fim < 0){
        printf("Não há o que remover!\n");
        return -1;
    }
    f->fim--;
}

int remover_meio(struct lista *f, int valor){
    int aux = encontrar(f, valor);
    if(aux == -1){
        printf("Valor não encontrado!\n");
        return -1;
    }

    while(aux <= f->fim){
        *(f->valores + aux) = *(f->valores + aux + 1);
        aux++;
    }

    f->fim--;
}


int encontrar(struct lista *f, int valor){
    int i = 0;
    int aux = -1;

    while(i <= f->fim){
        if(*(f->valores + i) == valor){
            aux = i;
            break;
        }
        i++;
    }

    return aux;
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
    add_inicio(f, 3);
    add_inicio(f, 2);
    add_inicio(f, 1);

    listar(f);

    add_meio(f, 2222222, 3);
    add_meio(f, 555555, 4);
    add_meio(f, 99999, 6);
    
    listar(f);

    remover_meio(f, 11111);
    remover_meio(f, 42);
    remover_meio(f, 3);

    listar(f);


    return 0;
}