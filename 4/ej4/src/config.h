#ifndef CONFIG_H
#define CONFIG_H
#include <semaphore.h>

#define MAX 4096
#define SEMAFORO "/semaforo"
#define SEM_ERROR() {perror("*** ERROR AL CREAR SEMAFORO ***");}
#define MAP_ERROR() {perror("*** ERROR AL MAPEAR OBJETO ***");}

#endif //CONFIG_H
