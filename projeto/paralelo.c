#include <stdio.h>
#include <gmp.h>
#include <omp.h> // Incluindo a biblioteca OpenMP

int main() {
    // Declarando variáveis para os números de precisão arbitrária
    mpz_t e, f;
    // Inicializando as variáveis
    mpz_init(e);
    mpz_init(f);
    
    // Definindo o número de dígitos decimais desejados
    int num_decimals = 2500000;
    // Calculando 10 elevado ao número de dígitos desejados e armazenando em 'e'
    mpz_ui_pow_ui(e, 10, num_decimals);
    // Inicializando 'f' com o valor de 'e'
    mpz_set(f, e);
    // Inicializando a variável de iteração 'k'
    int k = 1;
    
    // Iniciando a contagem de tempo
    double start_time = omp_get_wtime();
    
    // Loop principal
    while (mpz_sgn(f) > 0) {
        // Dividindo 'f' por 'k' e armazenando o resultado em 'f'
        mpz_fdiv_q_ui(f, f, k);
        // Adicionando 'f' a 'e'
        mpz_add(e, e, f);
        // Incrementando 'k'
        k++;
        // Imprimindo o valor de 'k' (serial)
        gmp_printf("%d\n", k);
    }
    
    // Finalizando a contagem de tempo
    double end_time = omp_get_wtime();
    // Calculando o tempo total
    double elapsed_time = end_time - start_time;
    
    // Imprimindo o valor final de 'e' e 'k' junto com o tempo de execução
    gmp_printf("%Zd %d\nTempo de execução: %.2f segundos\n", e, k, elapsed_time);

    // Liberando memória alocada para as variáveis
    mpz_clear(e);
    mpz_clear(f);
    
    return 0;
}
