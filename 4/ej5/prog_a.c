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

   if((cola_mensajes = mq_open(QUEUE_NAME,O_CREAT | O_RDWR, Q_PERMISSIONS,&atributos)) == -1){
        MQ_CREATE_ERROR();
        return 1;
    }

    char in;
    char in_buffer[MAX_MSG_SIZE];

    while(1){
        in = getchar();
        sprintf(in_buffer, "%c", in);
        
        if(mq_send(cola_mensajes, in_buffer,sizeof(in), 0) == -1){
            MQ_SEND_ERROR();
            return -1;
        }

        if(in == EOF) break;
    }
    mq_close(cola_mensajes);

}

