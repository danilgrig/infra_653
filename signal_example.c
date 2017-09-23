#include <signal.h> //signal
#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <unistd.h> //sleep


void my_handler(int nsig) {
	// nsig – номер сигнала, т.е. одну ф-ю можно использовать
	// для обработки нескольких сигналов
	printf("%d signal catched\n", nsig);
	if (nsig == 3) {
		exit(0);
	} else {
		printf("use cntl+\\ for exit\n");
	}
}

int main() {
	/* Выставляем реакцию процесса на сигнал SIGINT */
	printf("%d is SIGINT\n", SIGINT);
	signal(SIGINT, my_handler);

	for (;;) {
		sleep(1);
	}
}