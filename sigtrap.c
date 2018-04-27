/*
referencia sobre el funcionamiento de los breakpoint por software y depuradores
https://web.archive.org/web/20130605011618/http://www.technochakra.com:80/software-breakpoints/
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int pass_test = 0; // pasar prueba numero 8 porque si

// Controlador para señal sigtrap (breakpoint)
void ctrl_sigtrap (int signal){
	printf("\nsignal SIGTRAP[%d]\n", signal);
	pass_test = 8;
}

int main(int argc, char *argv[]) {

	int i = 0;

	// Se asigna el controlador
	if (signal(SIGTRAP, ctrl_sigtrap) == SIG_ERR){
		perror("Error set signal");
	}

	while(1) {
		pass_test = 0;
		printf("count %d\n", i+1);
		sleep(5);
		// crea breakpoint en ensamblador
		asm("int3"); // lanza la señal

		printf("\nvalid? %s | pass_test = %d\n", pass_test == 8 ? "true" : "false", pass_test);
		i++;
	}

	return 0;
}
