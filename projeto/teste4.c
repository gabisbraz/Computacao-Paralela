#include <stdio.h>
#include <gmp.h>
#include <omp.h>

#define PRECISION 1000000 // 1 milhão de casas decimais

// Função para calcular fatorial usando GMP
void mpz_factorial(mpz_t result, unsigned long int n) {
    mpz_set_ui(result, 1);
    for (unsigned long int i = 2; i <= n; i++) {
        mpz_mul_ui(result, result, i);
    }
}

int main() {
    // Inicializar variáveis GMP
    mpf_set_default_prec(PRECISION * 3.32193); // Definir precisão em bits (aprox. log2(10) * casas decimais)
    mpf_t sum, term;
    mpz_t fact;
    mpf_init(sum);
    mpf_init(term);
    mpz_init(fact);

    mpf_set_ui(sum, 0);

    // Número de termos a calcular; isso é uma aproximação
    unsigned long int num_terms = PRECISION; 

    // Paralelizar a soma usando OpenMP
    #pragma omp parallel for private(term, fact) shared(sum)
    for (unsigned long int n = 0; n < num_terms; n++) {
        // Calcular n!
        mpz_factorial(fact, n);
        
        // Calcular 1 / n!
        mpf_set_z(term, fact);
        mpf_ui_div(term, 1, term);
        
        // Seção crítica para atualizar a soma
        #pragma omp critical
        {
            mpf_add(sum, sum, term);
        }
    }

    // Imprimir o resultado
    gmp_printf("Soma de 1/n! com 1 milhão de casas decimais:\n%.1000000Ff\n", sum);

    // Limpar variáveis GMP
    mpf_clear(sum);
    mpf_clear(term);
    mpz_clear(fact);

    return 0;
}
