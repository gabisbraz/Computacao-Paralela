#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <omp.h>

// Função para calcular o fatorial
void calculate_factorial(mpf_t result, int n) {
    mpf_set_ui(result, 1);
    for (int j = 1; j <= n; ++j) {
        mpf_mul_ui(result, result, j);
    }
}

// Função para calcular o termo da série de Taylor
void calculate_term(mpf_t term, int i) {
    calculate_factorial(term, i);
    mpf_ui_div(term, 1, term);
}

int main() {
    // Declarando variáveis para os números de precisão arbitrária
    mpf_t e;
    mpf_set_default_prec(10000000); // Definindo a precisão padrão para 10 milhões de bits (cerca de 3 milhões de dígitos decimais)

    // Inicializando a variável
    mpf_init(e);
    mpf_set_ui(e, 0);

    // Definindo o número de termos da série de Taylor (para calcular 'e')
    int num_terms = 100;

    // Início da contagem de tempo
    double start_time = omp_get_wtime();

    // Vetor para armazenar os termos individualmente
    mpf_t terms[num_terms];

    // Inicializando os termos
    for (int i = 0; i < num_terms; ++i) {
        mpf_init(terms[i]);
    }

    // Loop principal paralelizado para calcular os termos
    #pragma omp parallel for
    for (int i = 0; i < num_terms; ++i) {
        calculate_term(terms[i], i);
        // Print para acompanhar o progresso do cálculo com ID da thread
        printf("Thread %d: Termo %d calculado.\n", omp_get_thread_num(), i);
    }

    // Inicializando uma soma local para cada thread
    int num_threads = omp_get_max_threads();
    mpf_t local_sums[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        mpf_init(local_sums[i]);
        mpf_set_ui(local_sums[i], 0);
    }

    // Loop principal paralelizado para somar os termos
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < num_terms; ++i) {
            mpf_add(local_sums[tid], local_sums[tid], terms[i]);
            mpf_clear(terms[i]); // Liberando memória alocada para o termo

            // Print para acompanhar o progresso da soma com ID da thread
            printf("Thread %d: Termo %d somado.\n", tid, i);
        }
    }

    // Somando as somas locais na variável global 'e'
    for (int i = 0; i < num_threads; ++i) {
        mpf_add(e, e, local_sums[i]);
        mpf_clear(local_sums[i]); // Liberando memória alocada para a soma local
    }

    // Fim da contagem de tempo
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Definindo a precisão de saída com base no número de termos da série de Taylor
    mp_exp_t exponent;
    char *e_str = mpf_get_str(NULL, &exponent, 10, 0, e);

    // Imprimindo o valor final de 'e' com a precisão ajustada
    printf("e: %.*s\n", num_terms + 2, e_str);

    // Imprimindo o tempo de execução
    printf("Tempo de execução: %.2f segundos\n", elapsed_time);

    // Liberando memória alocada para as variáveis
    mpf_clear(e);
    free(e_str); // Liberando memória alocada para a string

    return 0;
}
