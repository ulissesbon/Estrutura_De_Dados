#include <stdio.h>
#include <stdlib.h>

void medias(float **a, float **b, float **c, float **m){

    **m = (**a) + (**b) + (**c);
    print("Soma dos números: %f\n", **m);
    
    **m = **m / 3;
}


int main(){

    float *n1, *n2, *n3, *media;
    
    n1 = malloc(sizeof(float));
    n2 = malloc(sizeof(float));
    n3 = malloc(sizeof(float));
    media = malloc(sizeof(float));

    printf("Digite 3 números reais:\n");
    scanf("%f", n1);
    scanf("%f", n2);
    scanf("%f", n3);

    medias(&n1, &n2, &n3, &media);

    printf("Média: %f", *media);

    free(n1);
    free(n2);
    free(n3);
    free(media);

    return 0;
}