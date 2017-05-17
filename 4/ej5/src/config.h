#ifndef _CONFIG_H
#define _CONFIG_H

#define MAX_MSG_SIZE 4096
#define Q_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10
#define QUEUE_NAME "/my-mq"

#define MQ_CREATE_ERROR() perror("*** Create Queue Failed  ***");
#define MQ_SEND_ERROR() perror("*** Queue Send Error ***");
#define MQ_OPEN_ERROR() perror("*** Open Reading Queue Error ***");
#define MQ_RECV_ERROR() perror("*** Receiving from Queue Error ***");

#endif
