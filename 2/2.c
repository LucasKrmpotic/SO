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
	signal(SIGALRM,catch_alarm);
	printf("\n*** TIMEOUT AMIGOL ***\n");
	exit(1);
}
int main (int agc, char const argv[]){

	signal(SIGALRM,catch_alarm);
	
	char *input;
	char *pass;
	while(1){
		clear();

		printf("login: ");

		scanf(" %m[^\n]", &input);

		printf("password: ");
			
		alarm(MAX_ALARM);

		scanf(" %m[^\n]", &pass);
		
		alarm(0);
		int status;
		if(fork()){
			//padre
			waitpid(-1,&status,0);
			clear();

		}
		else {
			//hijo
			execl("/bin/bash", "/bin/bash", NULL);
		}
		
	}

	return 0;

}
