#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ALARM 15
#define clear() printf("\033[H\033[J")
#define CMD "/bin/bash"

void catch_alarm(int signum){
	printf("\n*** TIMEOUT ***\n");
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
			execl(CMD, CMD, NULL);
		}
		
	}

	return 0;

}
