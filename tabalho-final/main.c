#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANDARES 25
#define MAX_ELEVADORES 6
#define MAX_PESSOAS 20

typedef enum { SUBINDO, DESCENDO } Direcao;

typedef struct {
    int andar_atual;
    Direcao direcao;
    int destinos[MAX_ANDARES];
    int num_destinos;
} Elevador;

typedef struct {
    int andar_atual;
    int destino;
    int tempo_entrada;
    int pessoa_id;
} Pessoa;

Elevador elevadores[MAX_ELEVADORES];
Pessoa pessoas[MAX_PESSOAS];
int num_elevadores, num_pessoas, max_andar;

void inicializar_elevadores() {
    for (int i = 0; i < num_elevadores; i++) {
        elevadores[i].andar_atual = 0;
        elevadores[i].direcao = SUBINDO;
        elevadores[i].num_destinos = 0;
    }
}

void processar_pessoas(int tempo_atual) {
    for (int i = 0; i < num_pessoas; i++) {
        if (pessoas[i].tempo_entrada == tempo_atual) {
            printf("Pessoa %d entra no andar %d e deseja ir para o andar %d\n", 
                    pessoas[i].pessoa_id, pessoas[i].andar_atual, pessoas[i].destino);
            // Aqui você deve adicionar lógica para escolher qual elevador irá atender a pessoa
            // Para simplicidade, isso não está implementado.
        }
    }
}

void mover_elevadores(int tempo_atual) {
    for (int i = 0; i < num_elevadores; i++) {
        if (elevadores[i].num_destinos > 0) {
            if (elevadores[i].direcao == SUBINDO) {
                elevadores[i].andar_atual++;
                if (elevadores[i].andar_atual >= elevadores[i].destinos[elevadores[i].num_destinos - 1]) {
                    elevadores[i].direcao = DESCENDO;
                }
            } else {
                elevadores[i].andar_atual--;
                if (elevadores[i].andar_atual <= elevadores[i].destinos[0]) {
                    elevadores[i].direcao = SUBINDO;
                }
            }
            printf("Elevador %d está no andar %d\n", i + 1, elevadores[i].andar_atual);
        }
    }
}

void processar_eventos(const char *entrada) {
    char buffer[100];
    int tempo, id, andar1, andar2;
    const char *ptr = entrada;

    // Ler o número máximo de andares
    sscanf(ptr, "AM_%d", &max_andar);
    ptr = strchr(ptr, ' ') + 1;

    // Inicializar elevadores
    while (sscanf(ptr, "E%d_%d_%c_%[^ ]", &id, &andar1, &buffer[0], buffer + 1) == 4) {
        elevadores[id - 1].andar_atual = andar1;
        elevadores[id - 1].direcao = (buffer[0] == 'S') ? SUBINDO : DESCENDO;
        elevadores[id - 1].num_destinos = 0;
        char *token = strtok(buffer + 1, ",");
        while (token) {
            elevadores[id - 1].destinos[elevadores[id - 1].num_destinos++] = atoi(token);
            token = strtok(NULL, ",");
        }
        ptr = strchr(ptr, ' ') + 1;
    }

    // Inicializar pessoas
    while (sscanf(ptr, "T%d_P%d_%c_%d_%d", &tempo, &id, &buffer[0], &andar1, &andar2) == 5) {
        pessoas[num_pessoas].tempo_entrada = tempo;
        pessoas[num_pessoas].pessoa_id = id;
        pessoas[num_pessoas].andar_atual = andar1;
        pessoas[num_pessoas].destino = andar2;
        num_pessoas++;
        ptr = strchr(ptr, ' ') + 1;
    }
}

int main() {
    const char *entrada = "AM_25 E1_04_S_6,9,8 E2_11_D_5,8,9,3,2,T E3_20_D_5,8,T,9 T5_P01_S_4_6 T8_P01_D_6_4 T9_P02_S_5_10 T10_P03_S_3_9 T10_P04_D_6_T T10_P05_S_8_15 T15_P06_D_9_2 T15_P07_S_2_13 T18_P08_D_8_T T21_P01_D_16_3 T21_P10_S_T_13 T21_P11_S_T_12 T23_P12_S_T_15 T28_P13_S_2_13";

    // Parse and process the events
    processar_eventos(entrada);

    // Initialize elevators
    num_elevadores = 3; // Number of elevators in the case
    num_pessoas = 13;   // Number of people in the case
    inicializar_elevadores();

    // Simulate for 30 seconds (or an appropriate time based on the case)
    for (int tempo = 0; tempo <= 30; tempo++) {
        printf("Tempo: %d segundos\n", tempo);
        processar_pessoas(tempo);
        mover_elevadores(tempo);
        printf("\n");
    }

    return 0;
}
