#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Ponteiros globais para alocação dinâmica
pthread_mutex_t *forks;
int NUM_PHILOSOPHERS;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    
    // Variavels para definir a ordem de pegar os garfos
    int first_fork, second_fork;

    // Logica hierárquica para evitar deadlock
    if (id % 2 == 0) {
        // Filósofos PARES pegam Esquerda primeiro
        // Pares: Esquerda -> Direita
        first_fork = left_fork;
        second_fork = right_fork;
    } else {
        // Filósofos ÍMPARES pegam Direita primeiro
        // Impares: Direita -> Esquerda
        first_fork = right_fork;
        second_fork = left_fork;
    }

    while (1) {
        printf("Filosofo %d esta pensando.\n", id);
        sleep(rand() % 3); // Simula o tempo de pensar

        // Pega os garfos na ordem definida
        printf("Filosofo %d esta tentando pegar garfo %d.\n", id, first_fork);
        pthread_mutex_lock(&forks[first_fork]);
        printf("Filosofo %d esta tentando pegar garfo %d.\n", id, second_fork);
        pthread_mutex_lock(&forks[second_fork]);

        printf("Filosofo %d esta comendo.\n", id);
        sleep(rand() % 2); // Simula o tempo de comer

        // Solta os garfos na ordem inversa
        pthread_mutex_unlock(&forks[second_fork]);
        pthread_mutex_unlock(&forks[first_fork]);
        printf("Filosofo %d terminou de comer e soltou os garfos %d e %d.\n", id, first_fork, second_fork);
    }
    return NULL;
}

// Função principal

// main(int argc, char *argv[]) cria uma interfce para definir o número de filósofos via linha de comando
// argc: número de argumentos da linha de comando
// argv: array de strings com os argumentos da linha de comando

int main(int argc, char *argv[]) {
    // Validação de entrada
    if (argc < 2) {
        printf("Erro: Informe o numero de filosofos! Ex: %s 5\n", argv[0]);
        return 1;
    }

    // Definição do número de filósofos
    // atoi converte string para inteiro
    // esse valor é usado para criar as threads e mutexes
    NUM_PHILOSOPHERS = atoi(argv[1]);
    if (NUM_PHILOSOPHERS <= 1) {
        printf("O numero de filosofos deve ser maior que 1.\n");
        return 1;
    }

    // Alocação de memória
    pthread_t *threads = malloc(NUM_PHILOSOPHERS * sizeof(pthread_t));
    forks = malloc(sizeof(pthread_mutex_t) * NUM_PHILOSOPHERS);
    int *ids = malloc(NUM_PHILOSOPHERS * sizeof(int));

    // Inicialização dos mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Criação das threads (filósofos)
    printf("Iniciando o jantar dos filosofos com %d filosofos.\n", NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Falha ao criar thread");
            return 1;
        }
    }

    // Espera pelas threads (na prática, elas rodam indefinidamente)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL); 
    }

    // Liberação de memória e destruição dos mutexes
    free(threads);
    free(forks);
    free(ids);

    return 0;
}