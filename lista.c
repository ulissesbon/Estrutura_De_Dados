#include <stdio.h>
#include <stdlib.h>

#define capacidade 10

struct lista{
    int tam;
    int cap;
    int vet[capacidade];
};

void init(struct lista *l){
    l->tam = 0;
    l->cap = capacidade;
}

int buscar(struct lista *l, int valor){
    int i = 0, index = -1;
    for(i ; i < l->tam ; i++){
        if(l->vet[i] == valor){
            index = i;
            break;
        }
    }
    return index;
}

int listar(struct lista *l){
    int i;
    for(i=0; i < l->tam ; i++){
        printf("%d\n", l->vet[i]);
    }

}

int inserir(struct lista *l, int valor){
    if(l->tam == l->cap || buscar(l, valor) != -1){
		printf("Vetor lotado ou valor já inserido!\n");
        return -1;
    }
    else{
        l->vet[l->tam] = valor;
        l->tam++;
        printf("Valor adicionado!\n");
    }

}

int alterar(struct lista *l, int valor, int novo_valor){
    if(buscar(l, valor) != -1){
        l->vet[buscar(l, valor)] = novo_valor;
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
                l->vet[i] = l->vet[i+1];
                i++;
            }
        }
        l->tam = l->tam-1;
        printf("Valor excluido com sucesso!\n");
    }
}

int ordenar(struct lista *l){
    int aux;
    int i,j;
    for(i = 0 ; i < l->tam ; i++){
        for (j = 0 ; j < l->tam - 1 - i ; j++){
            if(l->vet[j]  >  l->vet[j + 1]){
                aux = l->vet[j];
                l->vet[j] = l->vet[j + 1];
                l->vet[j + 1] = aux;
            }
        }
    }
}

int main(){

	
	
    struct lista ls;
    init(&ls);
    inserir(&ls, 3);
    inserir(&ls, 2);
    inserir(&ls, 2);
    inserir(&ls, 10);
    inserir(&ls, 6);
    listar(&ls);
    printf("\n\n");
    excluir(&ls, 10);
    inserir(&ls, 12);
    inserir(&ls, 5);
    ordenar(&ls);
    listar(&ls);


    return 0;
}
