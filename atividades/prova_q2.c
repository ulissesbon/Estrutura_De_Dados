#include <stdio.h>
#include <stdlib.h>

struct lista{
    int capacidade;
    int tamanho;
    int *dados;
};


void init(struct lista *l, int capac){
    l->capacidade = capac;
    l->tamanho = 0;
    l->dados = malloc(capac * sizeof(int));
}


int inserir_comeco(struct lista *l, int valor){
    if(l->tamanho == l->capacidade){
        printf("Lista cheia!\n");
        return -1;
    }

    int i = l->tamanho;
    while(i > 0){
        *(l->dados + i) = *(l->dados + i - 1);
        i--;
    }
    *(l->dados) = valor;
    l->tamanho++;
}


int inserir_final(struct lista *l, int valor){
    if(l->tamanho == l->capacidade){
        printf("Lista cheia!\n");
        return -1;
    }

    int i = l->tamanho;
    *(l->dados + i) = valor;
    l->tamanho++;

}


int buscar(struct lista *l, int valor){
    int i = 0;
    int indice = -1;
    while(i < l->tamanho){
        if(valor == *(l->dados + i)){
            indice = i;
            break;
        }
        i++;
    }
    return indice;
}


int alterar(struct lista *l, int valor, int novo_valor){
    int i = buscar(l, valor);
    if(i == -1){
        return -1;
    }
    *(l->dados + i) = novo_valor;
}


int excluir(struct lista *l, int valor){
    int i = buscar(l, valor);
    if(i == -1){
        return -1;
    }
    while(i < l->tamanho - 1){
        *(l->dados + i) = *(l->dados + i + 1);
        i++;
    } 
    l->tamanho--;
}

int imprimir(struct lista *l){
    if(l->tamanho == 0)
        return -1;
    
    printf("[");
    for(int i = 0; i < l->tamanho; i++){
        printf(" %d ", *(l->dados + i));
    }
    printf("]\n");
    
}


int main(){

    struct lista ls;
    init(&ls, 10);
    inserir_comeco(&ls, 8);
    inserir_comeco(&ls, 32);
    inserir_comeco(&ls, 75);
    inserir_comeco(&ls, 51);
    inserir_comeco(&ls, 20);
    imprimir(&ls);

    inserir_final(&ls, 13);
    inserir_final(&ls, 105);
    inserir_final(&ls, 1);
    inserir_final(&ls, 42);
    inserir_final(&ls, 99);
    imprimir(&ls);

    excluir(&ls, 32);
    excluir(&ls, 105);
    excluir(&ls, 20);
    imprimir(&ls);
    
    alterar(&ls, 8, 9);
    alterar(&ls, 1, 11);
    alterar(&ls, 99, 44);
    imprimir(&ls);



    return 0;
}