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
    int i = l->tam;
    for(i ; i > -1 ; i--){
        if(valor == l->vet[i]){
            return i;
        }
        else
            return -1;
    }
}

int listar(struct lista *l){
    int i;
    for(i=0; i < l->tam ; i++){
        printf("%d\n", l->vet[i]);
    }

}

int inserir(struct lista *l, int valor){
    if(l->tam == l->cap){
		printf("Valor já inserido ou vetor lotado!\n");
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
        printf("Valor inicial não encontrado!\n");
        return -1;
    }
}

int excluir(struct lista *l, int valor){
    if(buscar(l, valor) == -1){
        printf("Valor não encontrado!\n");
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
    int i = 0, j = 0;
    for(i ; i < l->tam ; i++){
        for (j ; j < l->tam ; j++){
            if(l->vet[i]  >  l->vet[j]){
                aux = l->vet[i];
                l->vet[i] = l->vet[j];
                l->vet[j] = aux;
            }
        }
    }
}

int main(){

	int a=2;
	
    struct lista ls;
    init(&ls);
    inserir(&ls, a);
    listar(&ls);


    return 0;
}

