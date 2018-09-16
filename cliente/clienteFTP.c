/*
Client

create a socket with socket()
connect the socket to the address of the server connect()
send and receive data using  read() write()

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

//argv[1] = host_do_servidor
//argv[2] = porto_do_servidor
//argv[3] = nome_arquivo
//argv[4] = tam_buffer


int main(int argc, char *argv[]) {


  //Processa entradas
  int tam_buffer = atoi(argv[4]);
  int port = atoi(argv[2]);
  char *buffer;
  buffer = malloc(tam_buffer);
  //gettimeofday(&end, NULL);

  //Cria a socket
  int socketid;
  socketid = socket(AF_INET,SOCK_STREAM,0);

  //Especifica o endereço do socket do cliente
  struct sockaddr_in server_adress;
  server_adress.sin_family = AF_INET;
  server_adress.sin_port = htons(port);//passa o número da porta
  server_adress.sin_addr.s_addr = INADDR_ANY;
  //server_adress.sin_addr.s_addr = inet_addr("127.0.0.1");

  //conecta ao servidor
  int status = connect(socketid, (struct sockaddr *) &server_adress, sizeof(server_adress));
  if (status == -1){
    printf("Erro ao estabelecer a conexao\n");
  }
  /*else
    printf("status = %d, conexao estabelecida\n",status);*/

  //envia nome_arquivo
  if (sizeof(argv[3]) >= tam_buffer)
    printf("%s is too long!\n",argv[3]);
  else
    strcpy(buffer, argv[3]);
  int n;
  n = write(socketid,buffer,tam_buffer);

  //abre arquivo a ser salvo
  FILE * fp;
  fp = fopen (buffer, "w+");

  //recebe arquivo
  while(1){
    n = read(socketid,buffer,tam_buffer);
    if (n<tam_buffer){
      char aux[n];
      strncpy(aux, buffer, n);
      fprintf(fp, "%s",aux );
      break;
    }
    else{
      fprintf(fp, "%s",buffer );
    }
  }

  //fecha arquivo e socket
  fclose(fp);
  close(socketid);


  return 0;

}
