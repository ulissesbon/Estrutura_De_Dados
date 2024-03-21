#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define capacidade 10

struct aluno{
    char nome[100];
    char matricula[14];
};

struct lista{
    int tam;
    int cap;
    struct aluno *palunos[capacidade];
};

void init(struct lista *l){
    int i;
    
    l->tam = 0;
    l->cap = capacidade;
    for(i = 0; i < l->cap; i++){
        l->palunos[i] = NULL;
    }
}

void free_struct(struct lista *l){
    int i = 0;
    for(i = 0; i < l->tam; i++){
        free(l->palunos[i]);
    }
}

int buscar(struct lista *l, char matricula){
    int i = 0, index = -1;
    for(i ; i < l->tam ; i++){
        char aux = *(l->palunos[i])->matricula;
        if(strcmp(aux, matricula)){
            index = i;
            break;
        }
    }
    return index;
}

int listar(struct lista *l){
    printf("Alunos matriculados:\n");
    for(int i = 0; i < l->tam; i++){
        printf("%d)Aluno: %s \nMatricula: %s;\n", i+1, *(l->palunos[i])->nome, *(l->palunos[i])->matricula);
        printf("-------------------------------");
    }
}

int inserir(struct lista *l, char nome, char matricula){
    if(l->tam == l->cap || buscar(l, matricula) >= 0){
		printf("Matriculas lotadas ou ja aluno matriculado!\n");
        return -1;
    }
    else{
        l->palunos[l->tam]= malloc(sizeof(struct aluno)); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        strcpy(*(l->palunos[l->tam])->nome, nome);
        strcpy(*(l->palunos[l->tam])->matricula, matricula);
        l->tam++;
        printf("Aluno matriculado com sucesso!\n");
    }
}

int alterar(struct lista *l, char matricula, char nome){
    if(buscar(l, matricula) != -1){
        printf("1) Alterar nome;\n2) Alterar matricula;\n3) Cancelar.\n");
        int op;
        scanf("%d", &op);
        while(op != 3){
            if(op == 1){
                *(l->palunos[buscar(l, matricula)])->nome = nome;
            }
            else if(op == 2){
                *(l->palunos[buscar(l, matricula)])->matricula = matricula;
            }
            else if(op == 3){
                break;
            }
            else
                printf("Opção inválida!");
        }
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
                *l->valores[i] = *l->valores[i + 1];
                i++;
            }
        }
        l->valores[l->tam] = NULL;
        free(l->valores[l->tam]);
        l->tam = l->tam-1;
        printf("Valor excluido com sucesso!\n");
    }
}

int ordenar(struct lista *l){
    int *aux;
    int i = 0, j = 0;
    for(i = 0 ; i < l->tam ; i++){
        for (j = 0 ; j < l->tam - 1 - i ; j++){
            if(*l->valores[j]  >  *l->valores[j + 1]){
                aux = l->valores[j];
                l->valores[j] = l->valores[j + 1];
                l->valores[j + 1] = aux;
            }
        }
    }
}

int main(){

	
	
    struct lista ls;
    init(&ls);
    inserir(&ls, 2);
    for(int i=1; i<=9; i++){
        inserir(&ls, i);
    }
    printf("\n\n");
    listar(&ls);
    printf("\n\n");
    ordenar(&ls);
    listar(&ls);
    printf("\n\n");
    excluir(&ls, 9);
    excluir(&ls, 5);
    excluir(&ls, 1);
    excluir(&ls, 2);
    listar(&ls);

    free_struct(&ls);



    return 0;
}
