#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void *multiplicaMatriz(void* valores_linha_coluna) {
	
    // 	Converte o argumento valores_linha_coluna passado para a função de thread em um ponteiro para um array de inteiros
	int *data = (int *)valores_linha_coluna;
	
    // Armazena valor da multiplicação
	int k = 0;
	
    // Armazena o tamanho da lista data
	int tamanho_lista = data[0];
	
    // Itera sobre os elementos da linha da primeira matriz e da coluna da segunda matriz, 
    // multiplicando-os e acumulando o resultado em k.
	for (int i = 1; i <= tamanho_lista; i++) {
		k += data[i]*data[i+tamanho_lista];
	}
	
    // 	Aloca dinamicamente memória suficiente para armazenar um inteiro e armazena o resultado do cálculo em p.
	int *p = (int*)malloc(sizeof(int));
	*p = k;
	
    // 	Termina a thread e retorna o valor p, que é um ponteiro para o resultado do cálculo do elemento da matriz resultante
	pthread_exit(p);
}

int main() {

    // Declara matriz e vetor com seus respectivos valores
    int matriz[3][2] = {{1, 4}, {3, 5}, {7, 8}};
    int vetor[2] = {10, 2};
	
    // 	Declara o tamanho (número de linhas e colunas) da matriz e vetor
	int linha1=3, coluna1=2;
	int linha2=2, coluna2=1;
	
	// Calcula o tamanho final do vetor resultantetamanho_vetor_final
	int tamanho_vetor_final = linha1*coluna2;
	
    // 	Aloca dinamicamente memória para um vetor de threads de tamanho "tamanho_vetor_final"
	pthread_t *threads;
	threads = (pthread_t*)malloc(tamanho_vetor_final*sizeof(pthread_t));
	
    // 	Para iterar a thread
	int count = 0;
	
    // 	Armazena os elementos que serão utilizados para a multiplicação
	int* data = NULL;
	
	for (int i=0; i<linha1; i++) {
		for (int j=0; j<coluna2; j++) {
				
			data = (int*)malloc((20)*sizeof(int));
			data[0] = coluna1;
	
	        // Armazenar Elementos da Linha da Primeira Matriz
			for (int m=0; m < coluna1; m++)
				data[m+1] = matriz[i][m];
	
	        // Armazenar Elementos do Vetor
			for (int m=0; m < linha2; m++)
				data[m+coluna1+1] = vetor[m];
			
		    //  Cria uma nova thread para calcular um elemento da matriz resultante
		    //  Função mult, calculará um único elemento da matriz resultante
			pthread_create(&threads[count++], NULL, multiplicaMatriz, (void*)(data));
				
		}
	}
	
    printf("\nRESULTADO: \n");
    for (int i = 0; i < tamanho_vetor_final; i++) {
        
        void *valor_linha;
        
        // Espera que a thread com o identificador threads[i] termine sua execução
        pthread_join(threads[i], &valor_linha);
        int *resultado = (int *)valor_linha;
        
        printf("%d\n", *resultado); // Imprime cada elemento em uma nova linha
        free(resultado); // Liberando memória alocada para cada resultado
    }

    free(threads); // Liberando memória alocada para o vetor de threads

    return 0;
}

