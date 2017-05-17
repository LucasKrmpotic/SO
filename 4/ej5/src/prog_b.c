#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "config.h"

/*
 * Sugerencia a la hora de ejecutar este programa:
 * Hacer ./prog_a y ./prog_b en ventanas de terminal
 * independientes
 *
 * */

int main(int argc, char **argv){

    // declaramos cola de mensajes
    mqd_t cola_mensajes;
    // atributos
    struct mq_attr atributos;
    atributos.mq_flags = 0;
    atributos.mq_maxmsg = 10;
    atributos.mq_msgsize = MAX_MSG_SIZE;
    atributos.mq_curmsgs = 0;

    // abrimos cola de mensajes
    if((cola_mensajes = mq_open(QUEUE_NAME, O_RDONLY)) == -1){
        MQ_OPEN_ERROR();
        return 1;
    }

    // buffer de lectura
    char read_buffer[MAX_MSG_SIZE];

    while(1){
        // recibimos de la cola de mensajes
        if(mq_receive(cola_mensajes, read_buffer, MAX_MSG_SIZE, 0) == -1){
            MQ_RECV_ERROR();
            return -1;
        }
        // si leermos EOF salimos
        if(*read_buffer == EOF) break;
        // si no, imprimimos por pantalla
        printf("%c",*read_buffer);
    }
    mq_close(cola_mensajes);

}
