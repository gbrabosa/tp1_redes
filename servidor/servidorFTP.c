/*
Server:

Create a socket with the socket()
Bind the socket to an address using the bind() (hostname:port)
Listen for connections with the listen()
Accept a connection with the accept()
Send and receive data using the read() and write()

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

//argv[1] = porta_servidor
//argv[2] = tam_buffer
int main(int argc, char *argv[]) {


  struct timeval start, end;


  //processa os argumentos
  int tam_buffer = atoi(argv[2]);
  int port = atoi(argv[1]);


  //cria o socket
  int server_socket;
  server_socket = socket(AF_INET,SOCK_STREAM,0);

  //Especifica o socket do server
  struct sockaddr_in server_adress;
  server_adress.sin_family = AF_INET;
  server_adress.sin_port = htons(port);//passa o número da porta
  server_adress.sin_addr.s_addr = INADDR_ANY;

  //Cria o bind para a porta e o ip
  bind(server_socket, (struct sockaddr *) &server_adress, sizeof(server_adress));

  //Faz abertura passiva e aguarda por conexao
  listen(server_socket, 5);

  //Aceita conexao
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);
  if (client_socket < 0) {
   perror("ERROR on accept");
   exit(1);
}
  //recebe nome do arquivo
  char *buffer;
  buffer = malloc(tam_buffer);
  int n;
  char nome_arquivo[256];
  int i = 0;
  int flag =0;
  while (1) {
    n = read(client_socket,buffer,tam_buffer);
    for (int k = 0; k < strlen(buffer); k++) {
      if(buffer[k] == '0'){
        flag = 1;
        break;
      }
      nome_arquivo[i+k] = buffer[k];
    }
    if(flag == 1)
      break;
    i = i + tam_buffer;
  }
  printf("Nome do arquivo: %s\n",nome_arquivo);
  //abre arquivo a ser enviado
  FILE * fp;
  fp = fopen (nome_arquivo, "rb");


  //Salva o tempo inicial
  gettimeofday(&start, NULL);

  //le e envia arquivo
  i = 0;
  int tam_arquivo = 0;
  while(1){
    n = fread(buffer, sizeof(char),tam_buffer,fp);
    if(n<tam_buffer){
      i = write(client_socket,buffer,n);
      tam_arquivo = tam_arquivo + i;
      break;
    }
    else{
      i = write(client_socket,buffer,n);
      tam_arquivo = tam_arquivo + i;
    }

  }
  //salva tempo final
  gettimeofday(&end, NULL);
  float Tempo = (float) ( end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1000000.0);
  printf("Tamanho do arquivo: %d bytes\n",tam_arquivo);
  printf("Tempo de envio : %f s\n" , Tempo);
  //calcula taxa de transferência
  float tx = ((float)tam_arquivo /1000) / Tempo ;

  printf("Taxa de Transferencia: %f kb/s\n", tx);
  fclose(fp);
  close(server_socket);

  return 0;
}
