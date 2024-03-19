#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysinfo.h> // Para obter o número de núcleos da CPU

#define MAX_THREADS 64 // Defina o máximo de threads permitido

int matriz[10][10] = {
    {1,  2,  3,  4,  5,  6,  7,  8,  9, 10},
    {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
    {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
    {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
    {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
    {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
    {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
    {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
    {91, 92, 93, 94, 95, 96, 97, 98, 99, 100}
};

int vetor[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

int linha1, coluna1, linha2, coluna2;

// Estrutura para passar argumentos para a função da thread
typedef struct {
    int start_row;
    int end_row;
} ThreadArgs;

void *multiplicaMatriz(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    int start_row = thread_args->start_row;
    int end_row = thread_args->end_row;

    // Processar a multiplicação da matriz
    for (int i = start_row; i < end_row; i++) {
        int k = 0;
        for (int j = 0; j < coluna2; j++) {
            k += matriz[i][j] * vetor[j];
        }
        printf("Resultado da linha %d: %d\n", i, k);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    linha1 = sizeof(matriz) / sizeof(matriz[0]);    // Obtém o número de linhas da matriz
    coluna1 = sizeof(matriz[0]) / sizeof(matriz[0][0]); // Obtém o número de colunas da matriz
    linha2 = coluna1; // O número de linhas da segunda matriz é igual ao número de colunas da primeira
    coluna2 = sizeof(vetor) / sizeof(vetor[0]);    // Obtém o número de colunas do vetor

    // Obter o número de núcleos da CPU
    int num_cores = get_nprocs();
    int num_threads = num_cores;

    if (num_threads > MAX_THREADS) {
        num_threads = MAX_THREADS;
    }

    pthread_t thread_handles[MAX_THREADS];
    ThreadArgs thread_args[MAX_THREADS];

    // Calcular quantas linhas cada thread irá processar
    int lines_per_thread = linha1 / num_threads;

    for (int i = 0; i < num_threads; i++) {
        // Configurar argumentos para a thread
        thread_args[i].start_row = i * lines_per_thread;
        thread_args[i].end_row = (i + 1) * lines_per_thread;
        if (i == num_threads - 1) {
            thread_args[i].end_row = linha1; // A última thread processa o restante das linhas
        }

        // Criar a thread
        pthread_create(&thread_handles[i], NULL, multiplicaMatriz, (void *)&thread_args[i]);
    }

    // Aguardar a conclusão das threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(thread_handles[i], NULL);
    }
    return 0;
}

