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

int buscar(struct lista *l, char *matricula){
    int i = 0, index = -1;
    for(i ; i < l->tam ; i++){
        if(!strcmp(l->palunos[i]->matricula, matricula)){
            index = i;
            break;
        }
    }
    return index;
}

int listar(struct lista *l){
    printf("Alunos matriculados:\n");
    for(int i = 0; i < l->tam; i++){
        printf("%d)Aluno: %s \nMatricula: %s;\n", i+1, l->palunos[i]->nome, l->palunos[i]->matricula);
        printf("\n-------------------------------\n");
    }
}

int inserir(struct lista *l, char* nome, char* matricula){
    if(l->tam == l->cap || buscar(l, matricula) >= 0){
		printf("Matriculas lotadas ou ja aluno matriculado!\n");
        return -1;
    }
    
    l->palunos[l->tam]= malloc(sizeof(struct aluno)); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    strcpy(l->palunos[l->tam]->nome, nome);
    strcpy(l->palunos[l->tam]->matricula, matricula);
    l->tam++;
    printf("Aluno matriculado com sucesso!\n");
}

int alterar(struct lista *l, char* matricula, char* nome){
    if(buscar(l, matricula) != -1){
        printf("1) Alterar nome;\n2) Alterar matricula;\n3) Cancelar.\n");
        int op;
        scanf("%d", &op);
        while(op != 3){
            if(op == 1){
                *l->palunos[buscar(l, matricula)]->nome = nome;
            }
            else if(op == 2){
                *l->palunos[buscar(l, matricula)]->matricula = matricula;
            }
            else if(op == 3){
                break;
            }
            else
                printf("Opção inválida!");
        }
    }
    else{
        printf("Aluno n�o encontrado!\n");
        return -1;
    }
}

int excluir(struct lista *l, char *matricula){
    if(buscar(l, matricula) == -1){
        printf("Aluno n�o encontrado!\n");
    }
    else{
        int i = buscar(l, matricula);
        while(i < l->tam){
            if(i == (l->tam-1)){
                break;
            }
            else{
                l->palunos[i] = l->palunos[i + 1];
                i++;
            }
        }
        l->palunos[l->tam] = NULL;
        free(l->palunos[l->tam]);
        l->tam = l->tam-1;
        printf("Aluno excluido com sucesso!\n");
    }
}

int ordenar(struct lista *l){
    int *aux;
    int i = 0, j = 0;
    for(i = 0 ; i < l->tam ; i++){
        for (j = 0 ; j < l->tam - 1 - i ; j++){
            if(strcmp(l->palunos[j]->nome, l->palunos[j + 1]->nome) > 0){
                aux = l->palunos[j];
                l->palunos[j] = l->palunos[j + 1];
                l->palunos[j + 1] = aux;
            }
        }
    }
}

int main(){

	
	
    struct lista ls;
    init(&ls);
    inserir(&ls, "Ulisses Goncalves Bonfim", "12345678901234");
    inserir(&ls, "Marcelo Antonio Dantas", "12354435234665");
    inserir(&ls, "Larissa Manoela", "12345678524665");
    listar(&ls);
    ordenar(&ls);
    listar(&ls);

    excluir(&ls, "12345678524665");
    listar(&ls);


    return 0;
}
