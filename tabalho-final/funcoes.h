#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct solicitacao {
    int tempo;
    int idPessoa;
    char sentido;
    int andarPartida;
    int andarDestino;
    struct solicitacao *prox;
} solicitacao;

typedef struct interna {
    int andar_partida;
    int andar_destino;
    char sentido;
    struct interna *prox;
}interna;

typedef struct parada {
    int andar;
    int tempo;
    struct parada *prox;
    struct parada *ant;
}parada;

typedef struct elevador {
    int num_elevador;
    int andaresPercorridos;
    int andarAtual;
    char estado; // 'P' = parado, 'S' = subindo, 'D' = descendo
    interna *c_internas;
    parada *paradasSubindo;
    parada *paradasDescendo;
    parada *paradasPercorridas;
    struct elevador *prox;
} elevador;

typedef struct torre{
    int numAndares;
    int numElevadores;
    elevador *elevadores;
    solicitacao *solicitacoes;
} torre;

typedef struct listaString{
    char string[255];
    struct listaString *ant;
    struct listaString *prox;
}listaString;

void inserir_string(listaString **s, char string[255]);

void inserir_solicitacao(torre *t, int tempo, int idPessoa, char sentido, int andarPartida, int andarDestino);

void inserir_parada_percorrida(parada **p, int andar, int tempo);

void inserir_parada_final(parada **p, int andar);

void inserir_parada_inicio(parada **p, int andar);

void inserir_parada_meio(parada **p, int andar, parada *anterior);

void inserir_parada_ordem(parada **p, int andar);

void inserir_parada_ordem_inversa(parada **p, int andar);

void remover_parada_comeco(parada **p);

void listar_paradas(parada *p);

void listar_paradas_percorridas(parada *p);

void listar_strings(listaString *l);

void listar_solicitacoes(solicitacao *s);

void listar_internas(interna *i, elevador *e);

void remover_comeco(listaString **l);

void finalizar_string_comeco (listaString **l);

parada *stringToArray(char *str);

void adicionar_parada_solicitacao(elevador *e, int andar);

void adicionar_chamada_interna(elevador *e, int andar_partida, int andar_destino, char sentido);

void remover_chamada_comeco(interna **i);

interna *remover_chamada_adicionada(interna **i, int andar_partida);

void adicionar_elevador(torre *t, int andarAtual, char estado, int elevador_ID);

void inicializar_paradas(torre *t, listaString *strings);

torre *tratamento_de_dados(char *input, listaString **strings);

void ordenacao(elevador **elevadores, int *vetor, int tam);

elevador *analise_elevador(torre **predio, solicitacao *s);

void checar_solicitacoes(torre *t, int tempoAtual);

void checar_chamadas_internas (elevador *e);

void mover_elevadores(torre *torre, int tempo);

void finalizar_simulacao(torre *t);

void simulacao(char *input);

#endif // FUNCOES_H_INCLUDED