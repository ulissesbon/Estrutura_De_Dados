#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "funcoes.h"

void inserir_string(listaString **s, char string[255]) {
    listaString *no = malloc(sizeof(listaString));
    strcpy(no->string, string);
    no->prox = NULL;
    if(!no)
        return;
    listaString *aux = *s;
    while(aux && aux->prox) {
        aux = aux->prox;
    }
    if(!aux) {
        *s = no;
        no->ant = NULL;
    } else {
        aux->prox = no;
        no->ant = aux;
    }
}

void inserir_solicitacao(torre *t, int tempo, int idPessoa, char sentido, int andarPartida, int andarDestino) {
    solicitacao *nova = (solicitacao*)malloc(sizeof(solicitacao));
    nova->tempo = tempo;
    nova->idPessoa = idPessoa;
    nova->sentido = sentido;
    nova->andarPartida = andarPartida;
    nova->andarDestino = andarDestino;
    nova->prox = NULL; // Inicializa o próximo ponteiro como NULL

    if (t->solicitacoes == NULL) { // Lista vazia
        t->solicitacoes = nova;
        return;
    }

    solicitacao *atual = t->solicitacoes;
    while (atual->prox != NULL) { // Percorre até o último nó
        atual = atual->prox;
    }
    atual->prox = nova; // Insere a nova solicitação no final
}

void inserir_parada_percorrida(parada **p, int andar, int tempo) {
    // Criação da nova parada
    parada *aux = malloc(sizeof(parada));
    if (!aux)
        return;
    aux->andar = andar;
    aux->tempo = tempo;
    aux->prox = NULL;
    aux->ant = NULL;

    if (*p) {
        parada *atual = *p;
        while (atual->prox) {
            atual = atual->prox;
        }
        atual->prox = aux;
        aux->ant = atual;
        return;
    }

    *p = aux;
}

void inserir_parada_final(parada **p, int andar) {
    // Verifica se o andar já existe na lista
    parada *atual = *p;
    while (atual) {
        if (atual->andar == andar) {
            return; // Não insere se o andar já existe
        }
        atual = atual->prox;
    }

    // Criação da nova parada
    parada *aux = malloc(sizeof(parada));
    if (!aux)
        return;
    aux->andar = andar;
    aux->prox = NULL;
    aux->ant = NULL;

    if (*p) {
        atual = *p;
        while (atual->prox) {
            atual = atual->prox;
        }
        atual->prox = aux;
        aux->ant = atual;
        return;
    }

    *p = aux;
}

void inserir_parada_inicio(parada **p, int andar) {
    // Verifica se o andar já existe na lista
    parada *atual = *p;
    while (atual) {
        if (atual->andar == andar) {
            return; // Não insere se o andar já existe
        }
        atual = atual->prox;
    }

    // Criação da nova parada
    parada *aux = malloc(sizeof(parada));
    if (!aux)
        return;
    aux->andar = andar;
    aux->prox = NULL;
    aux->ant = NULL;

    if (*p) {
        (*p)->ant = aux;
        aux->prox = *p;
        *p = aux;
        return;
    }

    *p = aux;
}

void inserir_parada_meio(parada **p, int andar, parada *anterior) {
    // Verifica se o andar já existe na lista
    parada *atual = *p;
    while (atual) {
        if (atual->andar == andar) {
            return; // Não insere se o andar já existe
        }
        atual = atual->prox;
    }

    // Criação da nova parada
    parada *aux = malloc(sizeof(parada));
    if (!aux)
        return;

    aux->andar = andar;
    aux->prox = NULL;
    aux->ant = NULL;

    if (*p) {
        aux->prox = anterior->prox;
        if (anterior->prox != NULL) {
            anterior->prox->ant = aux; // Atualiza o anterior do próximo nó
        }
        aux->ant = anterior;
        anterior->prox = aux;
        return;
    }

    *p = aux; // Caso a lista esteja vazia
}

void inserir_parada_ordem(parada **p, int andar) {
    // Se a lista estiver vazia ou se o andar for menor que o primeiro
    if (!*p || andar < (*p)->andar) {
        inserir_parada_inicio(p, andar);
        return;
    }

    // Percorre a lista para encontrar a posição correta
    parada *aux = *p;
    while (aux->prox && andar > aux->prox->andar) {
        aux = aux->prox;
    }

    // Se o novo nó deve ser inserido no final da lista
    if (aux->prox == NULL) {
        inserir_parada_final(p, andar);
    } else if (andar != aux->andar) {  // Evita inserção de duplicatas
        inserir_parada_meio(p, andar, aux);
    }
}

void inserir_parada_ordem_inversa(parada **p, int andar) {
    // Se a lista estiver vazia ou se o andar for maior que o primeiro (ordem inversa)
    if (!*p || andar > (*p)->andar) {
        inserir_parada_inicio(p, andar);
        return;
    }

    // Percorre a lista para encontrar a posição correta (ordem inversa)
    parada *aux = *p;
    while (aux->prox && andar < aux->prox->andar) {
        aux = aux->prox;
    }

    // Se o novo nó deve ser inserido no final da lista
    if (aux->prox == NULL) {
        inserir_parada_final(p, andar);
    } else if (andar != aux->andar) {  // Evita inserção de duplicatas
        inserir_parada_meio(p, andar, aux);
    }
}

void remover_parada_comeco(parada **p) {
    if(!*p) return;
    parada *aux = *p;
    *p = (*p)->prox;
    free(aux);
}

void listar_paradas(parada *p) {
    if (!p) {
        printf("Lista de paradas vazia!\n");
        return;
    }

    parada *aux = p;
    printf("[");
    while(aux) {
        printf("%d", aux->andar);
        if(aux->prox)
            printf(" -> ");
        aux = aux->prox;
    }
    printf("]\n");
}

void listar_paradas_percorridas(parada *p) {
    if (!p) {
        printf("Lista de paradas vazia!\n");
        return;
    }

    parada *aux = p;
    printf("[");
    while(aux) {
        printf("%d(%d)", aux->andar, aux->tempo);
        if(aux->prox)
            printf(" -> ");
        aux = aux->prox;
    }
    printf("]\n");
}

void listar_strings(listaString *l) {
    if(!l) {
        printf("\nLista Vazia!\n");
        return;
    }
    listaString *aux = l;
    printf("\n[");
    while(aux) {
        printf("{%s}", aux->string);
        if(aux->prox)
            printf(", ");
        aux = aux->prox;
    }
    printf("]\n");
}

void listar_solicitacoes(solicitacao *s) {
    if (!s) {
        printf("\nLista de solicitações vazia!\n");
        return;
    }

    solicitacao *aux = s; // Ponteiro auxiliar para percorrer a lista
    while (aux) {
        printf("Tempo: %d, ID Pessoa: %d, Sentido: %c, Andar Partida: %d, Andar Destino: %d\n",
               aux->tempo,
               aux->idPessoa,
               aux->sentido,
               aux->andarPartida,
               aux->andarDestino);
        aux = aux->prox; // Avança para a próxima solicitação
    }
}

void listar_internas(interna *i, elevador *e) {
    if (!i) {
        printf("Lista de chamadas internas vazia!\n");
        return;
    }

    interna *aux = i; // Ponteiro auxiliar para percorrer a lista
    printf("\nLista de Chamadas Internas Elevador %d: ", e->num_elevador);
    printf("[");
    while (aux) {
        printf("(%c: %d -> %d)", aux->sentido, aux->andar_partida, aux->andar_destino); // Exibe o andar de partida e destino
        if (aux->prox)
            printf(", "); // Adiciona vírgula se não for o último elemento
        aux = aux->prox; // Move para a próxima chamada interna
    }
    printf("]\n");
}

void remover_comeco(listaString **l) {
    if(!*l)
        return;
    listaString *aux = *l;
    *l = (*l)->prox;
    free(aux);
}

void finalizar_string_comeco (listaString **l) {
    while(*l) {
        remover_comeco(l);
    }
}

parada *stringToArray(char *str) {
    parada *inicio = NULL;
    char *tok;

    // Dividir a string em tokens
    tok = strtok(str, ",");
    while (tok != NULL) {
        if (strcmp(tok, "T") == 0) {
            inserir_parada_final(&inicio, 0); // Substitui 'T' por 0
        } else {
            inserir_parada_final(&inicio, atoi(tok));
        }
        tok = strtok(NULL, ",");
    }

    return inicio;
}

void adicionar_parada_solicitacao(elevador *e, int andar) {
    // Verifica o estado do elevador

    // Elevador subindo
    if (e->estado == 'S') { 
        if (andar > e->andarAtual) {
            // Inserir na lista de subida
            inserir_parada_ordem(&e->paradasSubindo, andar);
        } 
        else {
            // Inserir na lista de descida
            inserir_parada_ordem_inversa(&e->paradasDescendo, andar);
        }
    } 
    // Elevador descendo
    else if (e->estado == 'D') { 

        if (andar < e->andarAtual) {
            // Inserir na lista de descida
            inserir_parada_ordem_inversa(&e->paradasDescendo, andar);
        } 
        else {
            // Inserir na lista de subida
            inserir_parada_ordem(&e->paradasSubindo, andar);
        }
    } 
    // Elevador parado
    else if (e->estado == 'P') { 

        if (andar > e->andarAtual) {
            // Inserir na lista de subida
            inserir_parada_ordem(&e->paradasSubindo, andar);
            // Mudar o estado para subindo
            e->estado = 'S';
        } 
        else if (andar < e->andarAtual) {
            // Inserir na lista de descida
            inserir_parada_ordem_inversa(&e->paradasDescendo, andar);
            // Mudar o estado para descendo
            e->estado = 'D';
        }
    }
}

void adicionar_chamada_interna(elevador *e, int andar_partida, int andar_destino, char sentido) {
    interna *aux = malloc(sizeof(interna));
    if (!aux) return;
    aux->andar_partida = andar_partida;
    aux->andar_destino = andar_destino;
    aux->sentido = sentido;
    aux->prox = NULL;

    if (!e->c_internas) {
        // Se a lista estiver vazia, a nova chamada interna é a primeira
        e->c_internas = aux;
    } 
    else {
        // Caso contrário, percorremos até o final da lista e adicionamos a nova chamada
        interna *temp = e->c_internas;
        while (temp->prox) { // Não é necessário verificar se temp é NULL, já que temp sempre será != NULL aqui
            temp = temp->prox;
        }
        temp->prox = aux;
    }
}


void remover_chamada_comeco(interna **i) {
    if (!*i)
        return;
    interna *aux = *i;
    *i = (*i)->prox;
    free(aux);
}

interna *remover_chamada_adicionada(interna **i, int andar_partida) {

    if (!*i)    // Lista vazia, nada a remover
        return NULL; 

    interna *atual = *i;
    interna *anterior = NULL;

    // Percorre a lista procurando o nó com o andar de partida correspondente
    while (atual && atual->andar_partida != andar_partida) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se não encontrar o nó, retorna
    if (!atual)
        return atual;

    // Se o nó a ser removido é o primeiro
    if (anterior == NULL) {
        *i = atual->prox; // Atualiza o início da lista
    } 
    else {
        // Caso contrário, remove o nó da lista
        anterior->prox = atual->prox;
    }

    // Salva o próximo nó antes de liberar o nó removido
    interna *proximo = atual->prox;

    // Libera o nó removido
    free(atual);

    // Retorna o próximo nó após a remoção
    return proximo;
}


void adicionar_elevador(torre *t, int andarAtual, char estado, int elevador_ID) {
    elevador *novoElevador = malloc(sizeof(elevador));
    novoElevador->andarAtual = andarAtual;
    novoElevador->estado = estado;
    novoElevador->andaresPercorridos = 0;
    novoElevador->prox = NULL; // Inicializa o próximo ponteiro como NULL
    novoElevador->num_elevador = elevador_ID;

    // Lista vazia
    if (t->elevadores == NULL) { 
        t->elevadores = novoElevador; // Define o novo elevador como o primeiro
    } 
    else {
        elevador *atual = t->elevadores;
        // Percorre até o último elevador
        while (atual->prox != NULL) { 
            atual = atual->prox;
        }
        atual->prox = novoElevador; // Insere o novo elevador no final
    }
}

void inicializar_paradas(torre *t, listaString *strings) {

    listaString *auxStrings = strings;
    elevador *auxElevador = t->elevadores;

    // Iterar sobre cada elevador e suas respectivas strings
    while (auxElevador && auxStrings) {

        // Converter a string atual em um array de paradas
        parada *listaParadas = stringToArray(auxStrings->string);

        parada *auxParadas = listaParadas;

        // Inserir cada parada no elevador atual
        while (auxParadas) {
            adicionar_parada_solicitacao(auxElevador, auxParadas->andar);
            auxParadas = auxParadas->prox;
        }

        // Avançar para o próximo elevador e próxima string
        auxStrings = auxStrings->prox;
        auxElevador = auxElevador->prox;
    }
}

torre *tratamento_de_dados(char *input, listaString **strings) {
    char *token;
    torre *t = malloc(sizeof(torre));
    t->solicitacoes = NULL; // Inicializa a lista de solicitações
    t->elevadores = NULL; // Inicializa a lista de elevadores
    t->numAndares = 0;

    // Dividir a string em tokens
    token = strtok(input, " ");

    // Verifica se o primeiro token é válido
    if (token != NULL) {
        // Tratar o primeiro token como número de andares
        t->numAndares = atoi(token + 3); // Extrai o número de andares do primeiro token
    }

    // Processar os tokens dos elevadores
    while ((token = strtok(NULL, " ")) != NULL) {

        if (token[0] == 'E') { // Se o token começa com 'E'
            int elevadorID;
            int andarAtual;
            char estado;
            char stringParadas[255];
            t->numElevadores++;

            // Exemplo de token: E1_04_S_6,9,8
            sscanf(token, "E%d_%d_%c_%s", &elevadorID, &andarAtual, &estado, stringParadas);

            inserir_string(strings, stringParadas);

            adicionar_elevador(t, andarAtual, estado, elevadorID);

        } else { // Se o token começa com 'T', é uma solicitação
            int tempo, idPessoa, andarPartida, andarDestino;
            char sentido;

            // Exemplo de token: T5_P01_S_4_6
            sscanf(token, "T%d_P%d_%c_%d_%d", &tempo, &idPessoa, &sentido, &andarPartida, &andarDestino);
            inserir_solicitacao(t, tempo, idPessoa, sentido, andarPartida, andarDestino);
        }
    }
    return t;
}


// função para ordenar a diferença de andares do elevador e da chamada
void ordenacao(elevador **elevadores, int *vetor, int tam) {
    for (int i = 1; i < tam; i++) {
        for (int j = 0; j < tam - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // Troca no vetor de inteiros
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;

                // Troca no vetor de elevadores (mantendo a consistência)
                elevador *aux1 = elevadores[j];
                elevadores[j] = elevadores[j + 1];
                elevadores[j + 1] = aux1;
            }
        }
    }
}


elevador *analise_elevador(torre **predio, solicitacao *s){

    int tamanho = (*predio)->numElevadores;

    // array de elevadores para serem analisados
    elevador **elevadores = malloc(tamanho * sizeof(elevador));
    elevador *atual = (*predio)->elevadores;

    // vetor para comparar a diferença entre os andares atuais e o andar solicitante
    int *comparador = malloc(tamanho * sizeof(int));

    for(int i = 0; i < tamanho; i++){
        //guarda um elevador em cada vetor
        elevadores[i] = atual;
        atual = atual->prox;
    }

    if (s->sentido == 'S') {
        for (int i = 0; i < tamanho; i++) {
            // verifica se o elevador está no mesmo sentido ou parado
            if ((elevadores[i]->estado == s->sentido && elevadores[i]->andarAtual < s->andarPartida ) ) {
                // diferença de andares, distância até a chamada
                comparador[i] = s->andarPartida - elevadores[i]->andarAtual;
            }
            else if (elevadores[i]->estado == 'P'){
                comparador[i] = abs(s->andarPartida - elevadores[i]->andarAtual);
            }
            else{
                comparador[i] = -25;  // Marca como não utilizável
            }
        }
    }
    else if (s->sentido == 'D') {
        for (int i = 0; i < tamanho; i++) {
            if ((elevadores[i]->estado == s->sentido && elevadores[i]->andarAtual > s->andarPartida )) {
                comparador[i] = elevadores[i]->andarAtual - s->andarPartida;
            }
            else if (elevadores[i]->estado == 'P'){
                comparador[i] = abs(s->andarPartida - elevadores[i]->andarAtual);
            }
            else{
                comparador[i] = -25;  // Marca como não utilizável
            }
        }
    }

    // ordena os elevadores com base na distancia
    ordenacao(elevadores, comparador, tamanho);

    // flag para comparação
    int selecionado = INT_MIN;

    for(int i = 0; i < tamanho; i++){
        if(comparador[i] >= 0){
            atual = elevadores[i];  //reuso o elevador auxiliar para receber o 
            selecionado = i;            // elevador mais próximo na direção de chamada
            break;
        }
    }

    // caso ele ache algum elevador capaz de atender a solicitação
    if(selecionado != INT_MIN){
        free(elevadores);
        free(comparador);
        return atual;
    }

    // caso não ache, irá procurar o que esteja parado
    for(int i = 0; i < tamanho; i++){
        if(elevadores[i]->estado == 'P'){
            atual = elevadores[i];
            free(elevadores);
            free(comparador);
            return atual;
        }
    }

    // caso nenhum se encaixe nos casos, ele irá deixar a solicitação para 
    return NULL;    // quando houver algum elevador disponível

}


void checar_solicitacoes(torre *t, int tempoAtual) {
    // Verifica se a lista de solicitações não é nula
    if (t->solicitacoes == NULL) {
        printf("Não há mais solicitações para serem atendidas!\n\n");
        return; // Retorna se não houver solicitações
    }

    // Ponteiro para percorrer a lista de solicitações
    solicitacao *aux = t->solicitacoes;
    solicitacao *ant = NULL; // Ponteiro para o nó anterior

    // Verifica se há solicitações no tempo atual
    while (aux != NULL) {
        if (aux->tempo == tempoAtual) {
            elevador *elevador_escolhido = analise_elevador(&t, aux);

            // caso tenha um elevador que possa atender a solicitação
            if(elevador_escolhido){
                // Remove a solicitação da lista

                if (ant == NULL) { // Se for o primeiro nó
                    t->solicitacoes = aux->prox;
                } 
                else { // Se não for o primeiro nó
                    ant->prox = aux->prox;
                }

                adicionar_parada_solicitacao(elevador_escolhido, aux->andarPartida);
                adicionar_chamada_interna(elevador_escolhido, aux->andarPartida, aux->andarDestino, aux->sentido);

                // Libera a memória alocada para a solicitação removida
                free(aux);

                // Atualiza o ponteiro aux para o próximo nó
                aux = t->solicitacoes;
            } 
            // caso não haja elevador para atender no momento
            else {
                aux->tempo++;   // coloco a solicitação para ser retestada no próximo ciclo
                ant = aux;
                aux = aux->prox;
            }
        } 
        
        else {
            ant = aux;
            aux = aux->prox; // Move para a próxima solicitação
        }
    }
}

// Verifica as chamadas internas dos elevadores
void checar_chamadas_internas (elevador *e) {

        if(!e->c_internas)
            return;  // se não houver solicitações, apenas retorna

        interna *aux = e->c_internas;

            // Verifica se há chamadas internas feitas no andar atual do elevador
            if (aux) {

                while (aux) {
                    // Se a chamada interna é para o andar atual do elevador, insere na lista de paradas
                    if (aux->andar_partida == e->andarAtual) {
                        
                        // Adiciona a chamada à lista de paradas
                        adicionar_parada_solicitacao(e, aux->andar_destino); 
                        
                        //chamada interna foi atendida (parada adicionada), remove a chamada da lista de chamadas
                        aux = remover_chamada_adicionada(&e->c_internas, aux->andar_partida);
                        continue;
                    }
                    aux = aux->prox;
                }
                aux = e->c_internas;
                listar_internas(aux, e);
            }
}

void mover_elevadores(torre *torre, int tempo) {
    elevador *e = torre->elevadores;

    printf("\nAtualização dos elevadores:");
    while (e) {
        printf("\n---------------------------\n");

        // Verifica se o elevador está parado e precisa de novas instruções
        if (e->estado == 'P') {
            if (e->paradasSubindo) {
                e->estado = 'S'; // Começa a subir
            } else if (e->paradasDescendo) {
                e->estado = 'D'; // Começa a descer
            } else {
                printf("Elevador %d está parado no andar %d\n", e->num_elevador, e->andarAtual);
                e = e->prox;
                printf("\n");
                continue;
            }
        }

        // Movimentação do elevador
        if (e->estado == 'S') { // Subindo
            if (e->paradasSubindo) {
                e->andarAtual++; // Sobe um andar
                printf("Elevador %d está SUBINDO para o andar %d\n", e->num_elevador, e->andarAtual);
                e->andaresPercorridos++;

                // Checa se chegou na parada desejada
                if (e->andarAtual == e->paradasSubindo->andar) {
                    remover_parada_comeco(&e->paradasSubindo);
                    printf("Elevador %d PAROU no andar %d\n", e->num_elevador, e->andarAtual);
                    inserir_parada_percorrida(&e->paradasPercorridas, e->andarAtual, tempo);
                }
            }

            // Verifica se ainda há paradas
            if (!e->paradasSubindo && e->paradasDescendo) {
                e->estado = 'D'; // Começa a descer
            } else if (!e->paradasSubindo && !e->paradasDescendo) {
                e->estado = 'P'; // Para o elevador
                printf("Elevador %d está parado no andar %d\n", e->num_elevador, e->andarAtual);
            }
        }
        else if (e->estado == 'D') { // Descendo
            if (e->paradasDescendo) {
                e->andarAtual--; // Desce um andar
                printf("Elevador %d está DESCENDO para o andar %d\n", e->num_elevador, e->andarAtual);
                e->andaresPercorridos++;

                // Checa se chegou na parada desejada
                if (e->andarAtual == e->paradasDescendo->andar) {
                    remover_parada_comeco(&e->paradasDescendo);
                    printf("Elevador %d PAROU no andar %d\n", e->num_elevador, e->andarAtual);
                    inserir_parada_percorrida(&e->paradasPercorridas, e->andarAtual, tempo);
                }
            }

            // Verifica se ainda há paradas
            if (!e->paradasDescendo && e->paradasSubindo) {
                e->estado = 'S'; // Começa a subir
            } else if (!e->paradasSubindo && !e->paradasDescendo) {
                e->estado = 'P'; // Para o elevador
                printf("Elevador %d está parado no andar %d\n", e->num_elevador, e->andarAtual);
            }
        }

        printf("Elevador %d: %c\nAndar Atual: %d\n", e->num_elevador, e->estado, e->andarAtual);
        checar_chamadas_internas(e);
        
        printf("Próximas paradas subindo: ");
        listar_paradas(e->paradasSubindo);
        
        printf("Próximas paradas descendo: ");
        listar_paradas(e->paradasDescendo);
        
        printf("Paradas percorridas: ");
        listar_paradas_percorridas(e->paradasPercorridas);

        e = e->prox; // Passa para o próximo elevador
    }
}

void finalizar_simulacao(torre *t) {
    if(!t) return;

    //finalizar elevadores
    while (t->elevadores) {
        elevador *aux = t->elevadores;
        t->elevadores = t->elevadores->prox;
        free(aux);
    }
    free(t);
}


void simulacao(char *input) {

    listaString *strings = NULL;
    torre *t = tratamento_de_dados(input, &strings);

    inicializar_paradas(t, strings);

    finalizar_string_comeco(&strings);
    int num = t->numElevadores;
    int tempo = 0;
    while(1) {
        
        sleep(1);
        printf("\nTEMPO ATUAL %d:\n", tempo);

        checar_solicitacoes(t,tempo);


        mover_elevadores(t, tempo);

        int todosParados = 1; // Flag para verificar se todos os elevadores estão parados

        // Verifica o estado de cada elevador
        elevador *e = t->elevadores;
        while (e) {
            if (e->estado != 'P') {
                todosParados = 0; // Algum elevador não está parado
                break; // Não precisa verificar mais, podemos sair do loop
            }
            e = e->prox;
        }

        if (todosParados) {
            elevador *aux = t->elevadores;
            int total = 0;
            while(aux){
                total += aux->andaresPercorridos;
                aux = aux->prox;
            }
            printf("\n\n##################################################\n\n");
            aux = t->elevadores;
            while(aux){
                printf("String de saída E%d: ", aux->num_elevador);
                listar_paradas_percorridas(aux->paradasPercorridas);
                aux = aux->prox;
            }
            printf("\nNúmero de andares percorrido pelos elevadores %d: %d\n", num, total);
            finalizar_simulacao(t);
            break; // Se todos os elevadores estão parados, finaliza a simulação
        }
        tempo++;
    }
    printf("Tempo de deslocamento dos %d elevadores: %d!", num, tempo);
}
