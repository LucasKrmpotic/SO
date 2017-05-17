#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "config.h"

int main(int argc, char **argv){

    mqd_t cola_mensajes;
    struct mq_attr atributos;
    atributos.mq_flags = 0;
    atributos.mq_maxmsg = 10;
    atributos.mq_msgsize = MAX_MSG_SIZE;
    atributos.mq_curmsgs = 0;

   if((cola_mensajes = mq_open(QUEUE_NAME, O_RDONLY)) == -1){
        MQ_OPEN_ERROR();
        return 1;
    }

    char read_buffer[MAX_MSG_SIZE];

    while(1){
        
        if(mq_receive(cola_mensajes, read_buffer, MAX_MSG_SIZE, 0) == -1){
            MQ_RECV_ERROR();
            return -1;
        }
        if(*read_buffer == EOF) break;
        printf("%c",*read_buffer);
    }
    mq_close(cola_mensajes);

}
