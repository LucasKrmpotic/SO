#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ALARM 60
#define clear() printf("\033[H\033[J")

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
void catch_sigint(int signum){
	/*rutina de atención para la señal SIGINT*/
	printf("\nSIGINT RECIBIDO!\n");
	/*una vez recibida la señal, se desactiva la alarma pendiente
	y se la reestablece al tiempo inicial*/
	alarm(0);
	alarm(MAX_ALARM);
}


int main (int agc, char const argv[]){
	/*se configuran ambas señales y empieza a correr el tiempo
	programa principal se queda esperando*/
	signal(SIGALRM,catch_alarm);
	signal(SIGINT,catch_sigint);
	alarm(MAX_ALARM);
	printf("---COMIENZO---\n");
	
	while(1);
	
	return 0;

}
