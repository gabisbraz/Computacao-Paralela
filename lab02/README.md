### Passo a passo realizado

ssh -i .ssh/labsuser.pem ec2-user@IP

git clone git@github.com:gabisbraz/Computacao-Paralela.git

mkdir lab02

cd lab02

nano lab02.c

*Comando utilizado para compilar o programa* <br />
gcc -g -Wall -pthread lab02.c -lpthread -o lab02 

*Comando para executar o código lab02* <br />
./lab02

*Adicionar os arquivos para dar o 'commit'*<br />
git add .  <br />

 *[ADD] Adição do código 'lab02.c' para compilação em terminal Linux* <br />
git commit -m   <br />

 *Enviar as mudanças feitas para o repositório*  <br />
git push    <br />

**Executando o programa 'lab02', é possível comparar o resultado obtido com** <br />
**cálculos feitos previamente, o qual são os mesmos que os resultados obtidos.**
