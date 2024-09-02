#include <stdio.h>
#include <stdlib.h>

struct predio{
    int qntd_andares;
};


struct elevador{
    int qntd_andares;
    int direcao; //-1: descendo; 0: parado; +1: subindo
    int destino;   //andar destino
    int andar_atual;

    struct elevador *ant;
    struct elevador *prox;
};
typedef struct elevador elevador;


int add(elevador **e, int direcao, int andar){
    
}


int main(){



    return 0;
}
