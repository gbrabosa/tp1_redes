/*
Strem sockets
client-server
Host: localhost
2-tier architecture
Iteractive server
IP 127.0.0.1
Client:

create a socket with socket()
connect the socket to the address of the server connect()
send and receive data using  read() write()

Server:

Create a socket with the socket()
Bind the socket to an address using the bind() (hostname:port)
Listen for connections with the listen()
Accept a connection with the accept()
Send and receive data using the read() and write()*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

//argv[0] = host_do_servidor
//argv[1] = porto_do_servidor
//argv[2] = nome_arquivo
//argv[3] = tam_buffer


int main(int argc, char *argv[]) {
  struct timeval start, end;
  gettimeofday(&start, NULL);
  //gettimeofday(&end, NULL);
  char hostname[] = "localhost";
  printf("%s\n",hostname);

  return 0;
  }
