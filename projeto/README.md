## Cálculo de Euler com OpenMD

O objetivo deste projeto é desenvolver uma solução paralela que maximize o valor de S, alcançando a melhor aproximação possível para a constante matemática "e", usando a série de Taylor. A implementação utilizará técnicas de paralelismo para calcular um valor de "e" com a maior precisão possível.

### Instalação do OpenMP e da Biblioteca MPFR 

1. **GCC com suporte para OpenMP:**

    ```bash
    sudo apt-get install gcc
    ```

2. **Biblioteca MPFR:**

    ```bash
    sudo apt-get install libmpfr-dev
    ```
    
### Compilação do Programa

``` bash
gcc -o projeto projeto.c -lmpfr -lgmp -fopenmp
```
### Execução do Programa
```
./calcular_e
```

### Biblioteca MPFR
`mpfr_t soma`: Armazena a soma total dos termos calculados. <br>
`mpfr_t soma_parcial[omp_get_max_threads()]`: Array que armazena as somas parciais calculadas por cada thread. <br>
``mpfr_t termo``: Armazena o valor do termo atual da série para cada iteração. <br>
``mpfr_t fatorial``: Armazena o fatorial atual para cada iteração. <br>
``mpfr_t resultado``: Parâmetro da função calcular_e onde o resultado final do cálculo de "e" será armazenado. <br>

#### Funções:

``mpfr_inits2(PRECISAO, soma, NULL)``: Inicializa o valor de "soma" com a precisão especificada. <br>
``mpfr_init2(soma_parcial[i], PRECISAO)``: Inicializa cada elemento do array "soma_parcial" com a precisão especificada. <br>
``mpfr_inits2(PRECISAO, termo, fatorial, NULL)``: Inicializa os valores de "termo" e "fatorial" com a precisão especificada. <br>
``mpfr_clears(termo, fatorial, NULL)``: Limpa as variáveis termo e fatorial após o uso. <br>
``mpfr_add(soma, soma, soma_parcial[i], MPFR_RNDN)``: Adiciona o valor de "soma_parcial[i]" à "soma", com o modo de arredondamento especificado. <br>
``mpfr_set(resultado, soma, MPFR_RNDN)``: Copia o valor de "soma" para "resultado", com o modo de arredondamento especificado. <br>
``mpfr_clear(soma)``: Limpa a variável "soma" após o uso.<br>
