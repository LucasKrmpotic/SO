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

    //Cola de mensajes
    mqd_t cola_mensajes;
    //Atributos de dicha cola 
    struct mq_attr atributos;
    atributos.mq_flags = 0;
    atributos.mq_maxmsg = 10;
    atributos.mq_msgsize = MAX_MSG_SIZE;
    atributos.mq_curmsgs = 0;

    // creamos cola de mensajes
    if((cola_mensajes = mq_open(QUEUE_NAME,O_CREAT | O_RDWR, Q_PERMISSIONS,&atributos)) == -1){
        MQ_CREATE_ERROR();
        return 1;
    }

    // caracter ingresado por entrada estandard
    char in;
    // buffer para enviar el mensaje
    char in_buffer[MAX_MSG_SIZE];

    while(1){
        in = getchar();
        //imprimimos en buffer el caracter
        sprintf(in_buffer, "%c", in);
        
        // enviamos a través de la cola de mensajes
        if(mq_send(cola_mensajes, in_buffer,sizeof(in), 0) == -1){
            MQ_SEND_ERROR();
            return -1;
        }

        // si encontramos EOF, salimos
        if(in == EOF) break;
    }
    // cerramos cola de mensajes|
    mq_close(cola_mensajes);

}

