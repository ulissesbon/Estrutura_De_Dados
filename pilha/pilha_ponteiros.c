#include <stdlib.h>
#include <stdio.h>


typedef struct pilha{
    int topo;
    int capac;
    int *valores;
} pilha;

void init(struct pilha *p){
    p->capac = 10;
    p->topo = -1;
    p->valores = malloc(10 * sizeof(int));
}

int adicionar_fim(pilha *p, int valor){
    if(p->topo == p->capac - 1){
        printf("Pilha cheia!\n");
        return -1;
    }
    p->topo++;
    int i = p->topo;
    *(p->valores + i) = valor;
}

int adicionar_comeco(pilha *p, int valor){
    if(p->topo == p->capac - 1){
        printf("Pilha cheia!\n");
        return -1;
    }
    p->topo++;
    int i = p->topo;
    while(i > 0){
        *(p->valores + i) = *(p->valores + i - 1);
        i--;
    }
    *(p->valores + 0) = valor;
}

void remover_fim(pilha *p){
    p->topo--;
}

void remover_inicio(pilha **p){
    int i = 0;
    while (i < (*p)->topo){
        *((*p)->valores + i) = *((*p)->valores + i + 1);
        i++;
    }
    (*p)->topo--;
}

void listar(pilha *p){
    int i = 0;
    printf("[ ");
    while (i < p->topo){
        printf("%d ", *(p->valores + i));
        i++;
    }
    printf("]\n");
}

int main(){

    pilha p;

    init(&p);

    adicionar_fim(&p, 13);
    adicionar_fim(&p, 8);
    adicionar_comeco(&p, 99);
    adicionar_comeco(&p, 745);

    listar(&p);


    return 0;
}