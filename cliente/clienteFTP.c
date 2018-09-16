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
  int n;
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


  //envia nome_arquivo
    char *nome_arquivo;
    nome_arquivo = malloc(sizeof(argv[3]));
    strcpy(nome_arquivo, argv[3]);
    int i = 0;
    while(i<strlen(argv[3])){
      for (int k = 0; k < tam_buffer; k++) {
        if((i+k) < strlen(argv[3])){
          buffer[k] = nome_arquivo[i+k];
        }
        else
          buffer[k] = '0';
      }
      write(socketid,buffer,tam_buffer);
      i = i+tam_buffer;
    }


  //abre arquivo a ser salvo
  FILE * fp;
  fp = fopen (nome_arquivo, "w+");
  //recebe arquivo
  while(1){
    n = read(socketid,buffer,tam_buffer);
    if (n<tam_buffer){
      char *aux;
      aux = malloc(n*sizeof(char));
      strncpy(aux, buffer, n);
      fprintf(fp, "%s", aux);
      free(aux);
      break;
    }
    else{
      fprintf(fp, "%s",buffer );
    }
  }

  //fecha arquivo e socket
  free(buffer);
  fclose(fp);
  close(socketid);


  return 0;

}
