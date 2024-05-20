#include <stdio.h>
#include <gmp.h>
#include <omp.h>

int main() {
    // Declarando variáveis para os números de precisão arbitrária
    mpf_t e;
    mpf_set_default_prec(10000000); // Definindo a precisão padrão para 10 milhões de bits (cerca de 3 milhões de dígitos decimais)
    
    // Inicializando as variáveis
    mpf_init(e);
    mpf_set_ui(e, 0);

    // Definindo o número de termos da série de Taylor (para calcular 'e')
    int num_terms = 100;

    // Início da contagem de tempo
    double start_time = omp_get_wtime();

    // Loop principal paralelizado
    #pragma omp parallel for
    for (int i = 0; i < num_terms; ++i) {
        // Inicializando o termo
        mpf_t term;
        mpf_init(term);
        mpf_set_ui(term, 1);

        // Calculando o fatorial de i
        for (int j = 1; j <= i; ++j) {
            mpf_mul_ui(term, term, j);
        }

        // Calculando o termo da série de Taylor
        mpf_ui_div(term, 1, term);

        // Adicionando o termo ao valor de 'e'
        #pragma omp critical
        mpf_add(e, e, term);

        // Liberando a memória alocada para o termo
        mpf_clear(term);
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

    return 0;
}
