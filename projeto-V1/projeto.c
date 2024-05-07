#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main() {
    mpz_t e, f;
    mpz_init(e);
    mpz_init(f);

    clock_t start, end;
    double cpu_time_used;

    int num_decimals = 2500000;
    mpz_ui_pow_ui(e, 10, num_decimals);
    mpz_set(f, e);
    int k = 1;

    start = clock();

    while (mpz_sgn(f) > 0) {
        mpz_fdiv_q_ui(f, f, k);
        mpz_add(e, e, f);
        k++;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    gmp_printf("%Zd %d\n", e, k);
    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    mpz_clear(e);
    mpz_clear(f);

    return 0;
}
