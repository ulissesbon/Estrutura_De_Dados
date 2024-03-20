#include <stdio.h>

int main(){
    
    int n;
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &n);

    int mat[n][n];
    
    printf("Digite os termos da matriz:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    int a, aux=0;
    a=2*n;
    a=a-1;
    int soma[a];
    int soma1[a];

    for(int i=0; i<a; i++){
        soma[i]=0;
        soma1[i]=0;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
                soma[i+j]+=mat[i][j];
                if(i<j){
                    if(j-i==n-i-1){
                        soma1[aux]+=mat[i][j];
                    }
                }
                if(i==j){
                    soma1[aux]+=mat[i][j];
                }
                if(i>j){
                    if(i-j==n-i-1){
                        soma1[aux]+=mat[i][j];
                    }
                }
                aux++;
        }
    }

    for(int i=0; i<a; i++){
        printf("Soma da %dª diagonal secundária: %d\n", i+1, soma[i]);
    }
    printf("\n\n");
    for(int i=0; i<a; i++){
        printf("Soma da %dª diagonal primaria: %d\n", i+1, soma1[i]);
    }
    



return 0;
}