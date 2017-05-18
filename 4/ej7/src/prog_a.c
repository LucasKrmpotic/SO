#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	struct sockaddr_un address;
	int  socket_fd, nbytes;
	char buffer[256];

	socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		perror("socket()");
		return 1;
	}

	/* Incializar a 0 la mamoria */
	memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	sprintf(address.sun_path, "./demo_socket");

	if(connect(socket_fd, (struct sockaddr *) &address,
		                sizeof(struct sockaddr_un)) != 0)
	{
		perror("connect()");
		return 1;
	}
    char c;
	while(1)
	{
        //PRODUCTOR
    /*  Leo de la entrada estándar y si es quit salir*/
        nbytes = 0;
        while((c = getchar()) != '\n'){
            buffer[nbytes++] = c;
        }
		if(strncmp(buffer, "quit", 4) == 0)
			break;
    /*  Escribo en el soket el mensaje para  el prog_b*/
		write(socket_fd, buffer, nbytes);

	}
  // Cerramos la conexión antes de salir
	close(socket_fd);

	return 0;
}
