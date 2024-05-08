#include <stdio.h>
#include <gmp.h>
#include <omp.h>

int main() {
    // Declarando variáveis para os números de precisão arbitrária
    mpz_t e, f, k;
    // Inicializando as variáveis
    mpz_init(e);
    mpz_init(f);
    mpz_init(k);
    
    // Definindo o número de dígitos decimais desejados
    int num_decimals = 25;
    // Calculando 10 elevado ao número de dígitos desejados e armazenando em 'e'
    mpz_ui_pow_ui(e, 10, num_decimals);
    // Inicializando 'f' com o valor de 'e'
    mpz_set(f, e);
    // Inicializando 'k' com 1
    mpz_set_ui(k, 1);
    
    // Iniciando a contagem de tempo
    double start_time = omp_get_wtime();
    
    // Loop principal
    while (mpz_sgn(f) > 0) {
        // Calculando o fatorial de 'k'
        mpz_fac_ui(f, mpz_get_ui(k)); // Corrigindo o tipo de argumento passado para mpz_fac_ui()
        // Dividindo 'f' por 'k' e armazenando o resultado em 'f'
        mpz_fdiv_q(f, f, k);
        // Adicionando 'f' a 'e'
        mpz_add(e, e, f);
        // Incrementando 'k'
        mpz_add_ui(k, k, 1);
        // Imprimindo o valor de 'k' (serial)
        gmp_printf("%Zd\n", k);
    }
    
    // Finalizando a contagem de tempo
    double end_time = omp_get_wtime();
    // Calculando o tempo total
    double elapsed_time = end_time - start_time;
    
    // Imprimindo o valor final de 'e' e 'k' junto com o tempo de execução
    gmp_printf("%Zd\nTempo de execução: %.2f segundos\n", e, elapsed_time);

    // Liberando memória alocada para as variáveis
    mpz_clear(e);
    mpz_clear(f);
    mpz_clear(k);
    
    return 0;
}
