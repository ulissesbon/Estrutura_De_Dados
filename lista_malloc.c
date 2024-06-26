#include <stdio.h>
#include <stdlib.h>

#define capacidade 10

struct lista{
    int tam;
    int cap;
    int *valores;
};

void init(struct lista *l){
    l->tam = 0;
    l->cap = capacidade;
    l->valores = malloc(capacidade * sizeof(int));
}

void free_struct(struct lista *l){
    free(l->valores);
}

int buscar(struct lista *l, int valor){
    int i = 0, index = -1;
    for(i ; i < l->tam ; i++){
        if(*(l->valores + i) == valor){
            index = i;
            break;
        }
    }
    return index;
}

int listar(struct lista *l){
    int i;
    for(i=0; i < l->tam ; i++){
        printf("%d\n", *(l->valores + i));
    }
}

int ordenar(struct lista *l){
    int aux;
    int i = 0, j = 0;
    for(i = 0 ; i < l->tam ; i++){
        for (j = 0 ; j < l->tam - 1 - i ; j++){
            if(*(l->valores + j)  >  *(l->valores + j + 1)){
                aux = *(l->valores + j);
                *(l->valores + j) = *(l->valores + j + 1);
                *(l->valores + j + 1) = aux;
            }
        }
    }
}

int inserir_ordem(struct lista *l, int valor){
    if(l->tam == l->cap || buscar(l, valor) != -1){
		printf("Valor j� inserido ou vetor lotado!\n");
        return -1;
    }
    else{
        ordenar(l);
        int i = 0;
        while(*(l->valores + i) < valor && i < l->tam){
            i++;
        }
        int j = l->tam;
        for(j = l->tam; j>i; j--){
            *(l->valores + j) = *(l->valores + j - 1);
        }
        *(l->valores + i) = valor;
        l->tam++;
    }
}

int inserir_comeco(struct lista *l, int valor){
    if(l->tam == l->cap || buscar(l, valor) != -1){
		printf("Valor j� inserido ou vetor lotado!\n");
        return -1;
    }
    else{
        int i = l->tam;
        while(i > 0){
            *(l->valores + i) = *(l->valores + i -1);
            i--;
        }
        *(l->valores) = valor;
        l->tam++;

    }
}

int inserir_fim(struct lista *l, int valor){
    if(l->tam == l->cap || buscar(l, valor) != -1){
		printf("Valor j� inserido ou vetor lotado!\n");
        return -1;
    }
    else{
        int i = l->tam;
        *(l->valores + i)= valor;
        l->tam++;
        printf("Valor adicionado!\n");
    }

}

int alterar(struct lista *l, int valor, int novo_valor){
    if(buscar(l, valor) != -1){
        *(l->valores + buscar(l, valor)) = novo_valor;
    }
    else{
        printf("Valor inicial n�o encontrado!\n");
        return -1;
    }
}

int excluir(struct lista *l, int valor){
    if(buscar(l, valor) == -1){
        printf("Valor n�o encontrado!\n");
    }
    else{
        int i = buscar(l, valor);
        while(i < l->tam){
            if(i == (l->tam-1)){
                break;
            }
            else{
                *(l->valores + i) = *(l->valores + i + 1);
                i++;
            }
        }
        l->tam = l->tam-1;
        printf("Valor excluido com sucesso!\n");
    }
}



int main(){

	
	
    struct lista ls;
    init(&ls);
    inserir_ordem(&ls, 2);
    inserir_ordem(&ls, 9);
    inserir_ordem(&ls, 5);
    inserir_ordem(&ls, 1);
    inserir_ordem(&ls, 12);
    inserir_ordem(&ls, 24);
    

    listar(&ls);
    printf("\n\n");
    printf("\n\n");
    excluir(&ls, 9);
    excluir(&ls, 5);
    excluir(&ls, 1);
    excluir(&ls, 2);
    listar(&ls);
    free_struct(&ls);

    return 0;
}

