#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ALARM 5
#define clear() printf("\033[H\033[J")


void catch_alarm(int signum){

	printf("\n*** TIMEOUT ***\n");
	exit(1);
}
void catch_sigint(int signum){

	//signal(SIGINT,catch_sigint);
	printf("\nSIGINT RECIBIDO!\n");
	alarm(0);
	alarm(MAX_ALARM);
}


int main (int agc, char const argv[]){

	signal(SIGALRM,catch_alarm);
	signal(SIGINT,catch_sigint);
	alarm(MAX_ALARM);
	printf("---COMIENZO---\n");
	while(1);

	return 0;

}
