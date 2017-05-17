#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include "config.h"


int main()
{
	const char *nombre = "/compartido";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;

    sem_t *semaforo = sem_open(SEMAFORO, O_CREAT, 0700, 0);
    if(semaforo == SEM_FAILED){
        SEM_ERROR();
        return -1;
    }
	/* open the shared memory segment */
	shm_fd = shm_open(nombre, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("Fallo al abrir el objeto de memoria compartido\n");
        return -1;
	}

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
        MAP_ERROR();
        return -1;
	}

	printf("Consumer leyending: ");
	/* now read from the shared memory region */
    while(1){
        sem_wait(semaforo);
        if(*(char*)ptr == EOF) break;
        printf("%c", *(char*)ptr++);
    } 
    //	printf("%s\n",ptr);

	/* remove the shared memory segment */
	if (shm_unlink(nombre) == -1) {
		printf("Error removing %s\n",nombre);
		exit(-1);
	}

	return 0;
}
