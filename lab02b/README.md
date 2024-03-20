### Passo a passo realizado
```
ssh -i .ssh/labsuser.pem ec2-user@IP

cd Computacao-Paralela

mkdir lab02b

cd lab02b

nano lab02b.c
```

**Comando utilizado para compilar o programa** <br />
```gcc -g -Wall -pthread lab02b.c -lpthread -o lab02b ```

**Comando para executar o código lab02** <br />
```./lab02b```

**Comando para escolher a quantidade de cores utilizados e o tempo de execução (feitos para 1,2,4,6,8 processadores)** <br />
```time taskset -c 0 ./lab02b ```

**Para ver os detalhes do processador utilizado** <br />
```cat /proc/cpuinfo```

**Adicionar os arquivos para dar o 'commit'**<br />
```git add .  <br />```

**[ADD] Adição do código 'lab02b.c' para compilação em terminal Linux** <br />
```git commit -m   <br />```

 **Enviar as mudanças feitas para o repositório**  <br />
```git push    <br />```


### 1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
![image](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/565d2efa-fd08-4a67-a568-dec74915644a)

### 2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.
![image](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/c20d1d7d-8746-4431-93c9-ba72dfd870b6)

### 3. Como você acha que poderia melhorar o seu algoritmo para obter maior benefício com o paralelismo? Para provar seu ponto, refaça a solução com essa abordagem e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

#### Novo gráfico de Speedup 
![image](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/050b14a2-023a-4035-bdc9-96453120004c)

#### Novo gráfico de tempo de execução
![image](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/02cc2be3-d6a4-4fe2-9b84-67b2c93d1852)



#### Como obter um melhor eficiência? 
Uma forma de deixar o programa mais eficiente em relação ao código anterior seria criando um número de threads de acordo com a quantidade de *cores* que serão utilizadas, dessa forma não perdendo eficiência na criação de threads desnecessárias. 
