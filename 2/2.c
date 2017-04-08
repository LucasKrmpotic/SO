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

/************************************
 * Ejercicio implementado por:
 *      KRMPOTIC, Lucas
 *      SERRUYA ALOISI, Luciano
 *      TOLEDO MARGALEF, Pablo
 *
 * *********************************/

void catch_alarm(int signum){
	/*rutina de atención para la señal SIGALRM*/
	printf("\n*** TIMEOUT ***\n");
	exit(1);
}
int main (int agc, char const argv[]){
	//establecemos que la señal "SIGALRM" sea atendida con la función "catch_alarm"
	signal(SIGALRM,catch_alarm);
	
	char *input;
	char *pass;
	while(1){
		clear();

		printf("login: ");
		scanf(" %m[^\n]", &input);
		printf("password: ");
			
        /* una vez solicitada la contraseña,
         * empieza a correr el reloj para activar la alarma*/
		alarm(MAX_ALARM);

		scanf(" %m[^\n]", &pass);
		/*Si se ingresa la contraseña antes de que se acabe el tiempo
         * se desactiva la alarma*/
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
