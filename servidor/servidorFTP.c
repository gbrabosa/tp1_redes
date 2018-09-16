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
  n = read(client_socket,buffer,tam_buffer);

  //abre arquivo a ser enviado
  FILE * fp;
  fp = fopen (buffer, "rb");

  //le e envia arquivo
  int i;
  while(1){
    n = fread(buffer, sizeof(char),tam_buffer,fp);
    if(n<tam_buffer)
      i = write(client_socket,buffer,n);
      break;
  }
  fclose(fp);
  close(server_socket);

  return 0;
}
