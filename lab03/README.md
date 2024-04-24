## TESTES
### - Com diretiva crítica
#### x1=0 | x2=100 | n=100
<img width="424" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/60438f31-6c02-408b-8d8c-4c0f1fdbb461">
<img width="423" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/4b10b296-76d6-423b-8fd6-1ea32122e106">

#### x1=0 | x2=100 | n=50
<img width="427" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/df3a2c4d-1688-43bf-9603-2467133d2f97">
<img width="427" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/289df7c2-10a9-4647-a389-0ea773d55357">

#### x1=0 | x2=100 | n=200
<img width="421" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/53af0d45-26e8-47a9-aabb-3b2b92026e9e">
<img width="421" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/b7f450f6-60c9-4b0c-a232-c874d4c1fe48">

### - Sem diretiva crítica
#### x1=0 | x2=100 | n=100
<img width="434" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/70b0508e-1094-4dbd-947d-864d702c8791">
<img width="433" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/a8698f85-11d7-4359-bec7-ca8563b87717">

#### x1=0 | x2=100 | n=50
<img width="439" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/b43cbf98-7bae-4761-90a7-c187d089c6d8">
<img width="442" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/2ef303cf-0c23-406c-812b-8f646698da57">

#### x1=0 | x2=100 | n=200
<img width="430" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/13b101c2-cb15-4cc4-9f0d-f3d92d0bf84e">
<img width="428" alt="image" src="https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/8fda1f83-f426-4d9e-bd3e-48b9a5d73024">


## EXERCÍCIOS
#### 1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução

![Figure_1](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/8a791397-fe5d-4fce-a907-2c916fdbd04d)

#### 2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.

![Figure_2](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/458073e8-be56-45dd-97fb-fdbbf90d925e)

#### 3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

![Figure_3](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/683f8010-00ae-4bec-80bf-16ba4709ba19)

![Figure_4](https://github.com/gabisbraz/Computacao-Paralela/assets/96640975/cf1a78a8-64c5-41ea-bc7c-c29463cf2f08)

**CONSIDERAÇÕES:** Os tempos de execução sem a diretiva crítica são significativamente menores do que com a diretiva crítica. Isso pode indicar que a diretiva crítica adiciona overhead ao tempo de execução. No caso do speedup, é possível observar o oposto, uma vez que com a diretiva crítica, o speedup aumenta com mais processadores, chegando a 9.7911 para 6 processadores, mas cai para 8.7698 para 8 processadores; e sem a diretiva crítica, o speedup diminui ao adicionar mais processadores, exceto para 8 processadores, onde há ocorre um aumento para 1.0569. Isso sugere que a paralelização sem diretiva crítica pode enfrentar problemas de escalabilidade, enquanto a paralelização com diretivas críticas tem um aumento no overhead. 

