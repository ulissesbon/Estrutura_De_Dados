#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ELEVATORS 6
#define MAX_FLOORS 25
#define MAX_PEOPLE 100

// Estruturas de dados
typedef struct {
    int floor;
    char direction;
    int destinations[MAX_FLOORS];
    int dest_count;
    int current_floor;
    int total_distance;
} Elevator;

typedef struct {
    int id;
    int start_floor;
    int destination;
    int time;
} Person;

Elevator elevators[MAX_ELEVATORS];
Person people[MAX_PEOPLE];
int num_elevators, num_floors, num_people;

// Funções auxiliares
void parse_elevators(char *input);
void parse_people(char *input);
void simulate(int *time);
int find_best_elevator(int floor);
void move_elevators();
void print_status();
int calculate_total_distance();

int main() {
    char case_str[] = "AM_25 E1_04_S_6,9,8 E2_11_D_5,8,9,3,2,T E3_20_D_5,8,T,9 T5_P01_S_4_6 T8_P01_D_6_4 T9_P02_S_5_10 T10_P03_S_3_9 T10_P04_D_6_T T10_P05_S_8_15 T15_P06_D_9_2 T15_P07_S_2_13 T18_P08_D_8_T T21_P01_D_16_3 T21_P10_S_T_13 T21_P11_S_T_12 T23_P12_S_T_15 T28_P13_S_2_13";

    // Inicialização
    memset(elevators, 0, sizeof(elevators));
    num_elevators = 0;
    num_floors = 0;
    num_people = 0;

    // Parse the input case string
    char *token = strtok(case_str, " ");
    while (token != NULL) {
        if (strncmp(token, "AM_", 3) == 0) {
            num_floors = atoi(token + 3);
        } else if (strncmp(token, "E", 1) == 0) {
            parse_elevators(token);
        } else if (strncmp(token, "T", 1) == 0) {
            parse_people(token);
        }
        token = strtok(NULL, " ");
    }

    // Simulate the elevator movements and print the result
    int time = 0;
    simulate(&time);
    printf("Total Distance: %d\n", calculate_total_distance());

    return 0;
}

void parse_elevators(char *input) {
    int num;
    sscanf(input, "E%d", &num);
    Elevator *elevator = &elevators[num - 1];
    elevator->current_floor = atoi(strtok(NULL, "_"));
    elevator->direction = strtok(NULL, "_")[0];
    char *dest = strtok(NULL, "_");
    elevator->dest_count = 0;

    while (dest != NULL) {
        if (strcmp(dest, "T") == 0) break;
        elevator->destinations[elevator->dest_count++] = atoi(dest);
        dest = strtok(NULL, ",");
    }
    num_elevators++;
}

void parse_people(char *input) {
    int time, id, start, destination;
    char type;
    sscanf(input, "T%d_P%d_%c_%d_%d", &time, &id, &type, &start, &destination);

    Person *person = &people[num_people++];
    person->id = id;
    person->start_floor = start;
    person->destination = destination;
    person->time = time;
}

void simulate(int *time) {
    while (num_people > 0) {
        int i;
        for (i = 0; i < num_people; i++) {
            if (people[i].time == *time) {
                int best_elevator = find_best_elevator(people[i].start_floor);
                elevators[best_elevator].destinations[elevators[best_elevator].dest_count++] = people[i].destination;
            }
        }
        move_elevators();
        (*time)++;
    }
}

int find_best_elevator(int floor) {
    int best_elevator = 0;
    int min_distance = INT_MAX;

    for (int i = 0; i < num_elevators; i++) {
        int distance = abs(elevators[i].current_floor - floor);
        if (distance < min_distance) {
            min_distance = distance;
            best_elevator = i;
        }
    }
    return best_elevator;
}

void move_elevators() {
    for (int i = 0; i < num_elevators; i++) {
        Elevator *elevator = &elevators[i];
        if (elevator->dest_count == 0) continue;

        int next_floor = elevator->direction == 'S' ? elevator->destinations[0] : elevator->destinations[elevator->dest_count - 1];
        int distance = abs(elevator->current_floor - next_floor);
        elevator->total_distance += distance;
        elevator->current_floor = next_floor;

        if (elevator->direction == 'S') {
            if (elevator->current_floor == elevator->destinations[0]) {
                memmove(elevator->destinations, elevator->destinations + 1, (elevator->dest_count - 1) * sizeof(int));
                elevator->dest_count--;
                if (elevator->dest_count == 0) elevator->direction = 'D';
            }
        } else {
            if (elevator->current_floor == elevator->destinations[elevator->dest_count - 1]) {
                elevator->dest_count--;
                if (elevator->dest_count == 0) elevator->direction = 'S';
            }
        }
    }
}

int calculate_total_distance() {
    int total_distance = 0;
    for (int i = 0; i < num_elevators; i++) {
        total_distance += elevators[i].total_distance;
    }
    return total_distance;
}
