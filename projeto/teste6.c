#include <stdio.h>
#include <mpfr.h>
#include <omp.h>

#define PRECISION 2500
#define TERMS 2500
#define CHUNK_SIZE 100

void calculate_e(mpfr_t result, int depth) {
    mpfr_t term, sum;
    mpfr_inits2(PRECISION, term, sum, NULL);

    mpfr_set_ui(sum, 0, MPFR_RNDN); // Initialize sum to 0

    // Set the number of threads explicitly
    omp_set_num_threads(4); // Set the number of threads to 4, adjust as needed

    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Number of Threads: %d\n", omp_get_num_threads());
        }

        #pragma omp for private(term) schedule(static, CHUNK_SIZE)
        for (int i = 0; i <= depth; ++i) {
            mpfr_init2(term, PRECISION);

            mpfr_set_ui(term, 1, MPFR_RNDN); // Initialize term to 1

            // Calculate 1 / i!
            for (int j = 1; j <= i; ++j) {
                mpfr_div_ui(term, term, j, MPFR_RNDN);
            }

            // Add term to sum
            #pragma omp critical
            mpfr_add(sum, sum, term, MPFR_RNDN);

            mpfr_clear(term);

            // Print iteration
            printf("Iteration: %d\n", i);
        }
    }

    // Copy the sum to result after the parallel loop
    mpfr_set(result, sum, MPFR_RNDN);

    mpfr_clear(sum);
}

int main() {
    mpfr_t e;
    mpfr_init2(e, PRECISION);

    double start_time = omp_get_wtime(); // Record start time

    calculate_e(e, TERMS);

    double end_time = omp_get_wtime(); // Record end time

    double total_time = end_time - start_time;

    printf("Execution time: %.6f seconds\n", total_time);
    printf("Total number of threads used: %d\n", omp_get_max_threads());
    printf("Calculated e with %d decimal numbers:\n", PRECISION);
    mpfr_out_str(stdout, 10, PRECISION, e, MPFR_RNDN); // Print final e with specified precision
    printf("\n");

    mpfr_clear(e);

    return 0;
}

