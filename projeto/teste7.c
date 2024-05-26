#include <stdio.h>
#include <mpfr.h>
#include <omp.h>

#define PRECISAO 500000 // Precisão desejada para o cálculo de e
#define TERMOS 500000 // Número de termos para calcular e
#define TAMANHO_POR_BLOCO 20000 // Tamanho do bloco para divisão de trabalho

void calcular_e(mpfr_t resultado, int profundidade) {
    mpfr_t soma;
    mpfr_inits2(PRECISAO, soma, NULL);

    mpfr_set_ui(soma, 0, MPFR_RNDN); // Inicializa a soma como 0

    // Define o número de threads explicitamente
    omp_set_num_threads(10); // Define o número de threads como 10, ajustável conforme necessário

    // Array to hold partial sums for each thread
    mpfr_t soma_parcial[omp_get_max_threads()];
    for (int i = 0; i < omp_get_max_threads(); ++i) {
        mpfr_init2(soma_parcial[i], PRECISAO);
        mpfr_set_ui(soma_parcial[i], 0, MPFR_RNDN);
    }

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        mpfr_t termo, fatorial;
        mpfr_inits2(PRECISAO, termo, fatorial, NULL);

        mpfr_set_ui(fatorial, 1, MPFR_RNDN); // Inicializa fatorial como 1

        #pragma omp for schedule(static, TAMANHO_POR_BLOCO)
        for (int i = 0; i <= profundidade; ++i) {
            if (i > 0) {
                mpfr_mul_ui(fatorial, fatorial, i, MPFR_RNDN); // fatorial = fatorial * i
            }
            mpfr_ui_div(termo, 1, fatorial, MPFR_RNDN); // termo = 1 / fatorial
            mpfr_add(soma_parcial[id], soma_parcial[id], termo, MPFR_RNDN); // soma_parcial[id] += termo
        }

        mpfr_clears(termo, fatorial, NULL);
    }

    // Combine partial sums into the final result
    for (int i = 0; i < omp_get_max_threads(); ++i) {
        mpfr_add(soma, soma, soma_parcial[i], MPFR_RNDN);
        mpfr_clear(soma_parcial[i]);
    }

    // Copia a soma para o resultado após o loop paralelo
    mpfr_set(resultado, soma, MPFR_RNDN);

    mpfr_clear(soma);
}

int main() {
    mpfr_t e;
    mpfr_init2(e, PRECISAO);

    double inicio = omp_get_wtime(); // Registra o tempo de início

    calcular_e(e, TERMOS);

    double fim = omp_get_wtime(); // Registra o tempo de fim

    double tempo_total = fim - inicio;

    printf("Tempo de execução: %.6f segundos\n", tempo_total);
    printf("Número total de threads utilizadas: %d\n", omp_get_max_threads());

    // Abre o arquivo para escrever o resultado
    FILE *arquivo = fopen("resultado_e.txt", "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Escreve o valor de 'e' no arquivo
    mpfr_out_str(arquivo, 10, PRECISAO, e, MPFR_RNDN);
    fprintf(arquivo, "\n");

    // Fecha o arquivo
    fclose(arquivo);

    printf("O resultado foi salvo em 'resultado_e.txt'\n");

    mpfr_clear(e);

    return 0;
}
