ssh -i .ssh/labsuser.pem ec2-user@SEU_IP
ssh-keygen
yes
espaço x3
cat /home/ec2-user/.ssh/id_rsa.pub
sudo dnf install git
sudo dnf install nano
sudo dnf install gcc

Vai gerar a chave --> colocar no git hub e ativar selectbox que fica abaixo da chave sei

git clone git@github.com:NOME_USUARIO/NOME_DIRETORIO.git

ls

cd NOME_DO_SEU_DIRETORIO

se ls tiver README.md, então criar pasta lab01, caso contrário criar README.md

mkdir lab01

cd lab01

vi README.md (descrever lab01)
ESC + shift dois pontos + wq + enter 

nano lab01.c (escrever hello world em C)
"#include <stdio.h>

int main()
{
  printf("Hello World!\n");

  return 0;
}" 

git add .
git commit -m "Mensagem de sua preferência"
git push

para executar o código devemos:
gcc ­-o NOME_EXECUTAVEL NOME_CODIGO.c
./NOME_EXECUTAVEL

printar terminal fazendo o hello world para envio! 

 
