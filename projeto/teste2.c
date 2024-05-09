#include <stdio.h>
#include <gmp.h>
#include <omp.h>

int main() {
    // Declarando variáveis para os números de precisão arbitrária
    mpf_t e;
    // Inicializando as variáveis
    mpf_init(e);
    
    // Definindo o número de dígitos decimais desejados
    int num_decimals = 5;
    // Inicializando 'e' com o valor inicial da série de Taylor para Euler
    mpf_set_d(e, 1.0);

    // Iniciando a contagem de tempo
    double start_time = omp_get_wtime();
    
    // Calculando a série de Taylor para o número de Euler
    for (int i = 1; i <= 10000; ++i) {
        mpf_t term;
        mpf_init(term);
        mpf_set_d(term, 1.0);
        for (int j = 1; j <= i; ++j) {
            mpf_div_ui(term, term, j);
        }
        mpf_add(e, e, term);
        mpf_clear(term);
    }

    // Ajustando a precisão para o número de dígitos decimais desejados
    mpf_set_prec(e, num_decimals * 3.34); // 3.34 é aproximadamente log10(2)
    
    // Finalizando a contagem de tempo
    double end_time = omp_get_wtime();
    // Calculando o tempo total
    double elapsed_time = end_time - start_time;
    // Imprimindo o valor final de 'e' junto com o tempo de execução
    gmp_printf("Número de Euler com %d dígitos decimais:\n%.Ff\nTempo de execução: %.2f segundos\n", num_decimals, e, elapsed_time);

    // Liberando memória alocada para as variáveis
    mpf_clear(e);
    
    return 0;
}
