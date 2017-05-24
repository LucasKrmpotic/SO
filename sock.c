#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


#define PORT 3000 /* El puerto que será abierto */
#define BACKLOG 10 /* El número de conexiones permitidas */

typedef struct{
  struct sockaddr_in addr;
  int connfd;
  int uid;
} client_t;

client_t * clientes[10];



void * connection_handler(void * cli_aux)
{
  client_t* cli = (client_t *)cli_aux;
	int nbytes;
	char buffer[256];
  printf("UID: %d\n", cli->uid);

    // CONSUMIDOR
    // leo el mensaje y lo muestro por la salida estándar
    while(1){

      while((nbytes = read(cli->connfd, buffer, 256))>0)
      {
            buffer[nbytes] = 0;
            printf("%s\n", buffer);

            for (int i = 0; i < 10; i++){
              // printf("CLIENTE: %d\n", i);
              if(clientes[i] != NULL){
                // printf("ENVIANDO A UID: %d\n", clientes[i]->uid);
                if(clientes[i]->uid != cli->uid)
                  write(clientes[i]->connfd, buffer, strlen(buffer));
              }
            }
      }

    }
  // cierro la conexión
	close(cli->connfd);
	return 0;
}

int main()
{
   int uid = 0;
   int fd = 0, connfd = 0; /* los ficheros descriptores */
   struct sockaddr_in server;
   /* para la información de la dirección del servidor */
   struct sockaddr_in cli_addr;
   /* para la información de la dirección del cliente */
   int sin_size;
   pthread_t tid;
   /* A continuación la llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
      printf("error en socket()\n");
      exit(-1);
   }

   server.sin_family = AF_INET;

   server.sin_port = htons(PORT);
   /* ¿Recuerdas a htons() de la sección "Conversiones"? =) */

   server.sin_addr.s_addr = INADDR_ANY;
   /* INADDR_ANY coloca nuestra dirección IP automáticamente */

   bzero(&(server.sin_zero),8);
   /* escribimos ceros en el reto de la estructura */


   /* A continuación la llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server,
           sizeof(server))==-1) {
      printf("error en bind() \n");
      exit(-1);
   }

   if(listen(fd,10) == -1) {  /* llamada a listen() */
      printf("error en listen()\n");
      exit(-1);
   }

   while(1) {
      sin_size=sizeof(struct sockaddr_in);

      socklen_t clilen = sizeof(cli_addr);

      /* A continuación la llamada a accept() */
      if ((connfd = accept(fd,(struct sockaddr *)&cli_addr,
                        &clilen))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }

      client_t * cli = (client_t *)malloc(sizeof(client_t));
      cli-> addr = cli_addr;
      cli-> connfd = connfd;
      cli->uid = uid++;

      for (int i = 0; i<10; i++){
        if (!clientes[i]){
          clientes[i] = cli;
          break;
        }
      }

      pthread_create(&tid, NULL, &connection_handler, (void*)cli);
      // close(fd2); /* cierra fd2 */
   }
   return 0;
}


