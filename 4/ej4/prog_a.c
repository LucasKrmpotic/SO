#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include "config.h"


int main()
{
    //nombre para el objeto de memoria compartido
	const char *nombre = "/compartido";
    //file descriptor para el objeto de memoria compartido
	int shm_fd;
    //puntero al objeto en memoria
	void *ptr;
    
    sem_t *semaforo;

    //creamos el semaforo
    if((semaforo = sem_open(SEMAFORO, O_CREAT, 0700, 0)) == SEM_FAILED){
        SEM_ERROR();
        return -1;
    } 

	/* creamos el objeto de memoria compartida*/
	shm_fd = shm_open(nombre, O_CREAT | O_RDWR, 0666);

	/* truncamos el tamanio del objeto */
	ftruncate(shm_fd,MAX);

	/* mapeamos el objeto compartido a memoria local del proceso */
	ptr = mmap(0,MAX, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
        MAP_ERROR();
		return -1;
	}

    //leemos de stdin y escribimos a la memoria compartida
    char in;
    while(1){

       in = getchar();
       sprintf(ptr++, "%c", in);
       sem_post(semaforo);

       if(in == EOF)
           break;
           
    }

    /*
	printf("producer escribiending %s\n",message0);
	sprintf(ptr,"%s",message0);
	ptr += strlen(message0);
	printf("producer escribiending %s\n",message1);
	sprintf(ptr,"%s",message1);
	ptr += strlen(message1);
	printf("producer escribiending %s\n",message2);
	sprintf(ptr,"%s",message2);
	ptr += strlen(message2);
    */

	return 0;
}
