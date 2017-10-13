#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	int *array;
	int shmid;
	int is_new = 1;
	key_t key = 123; /* IPC ключ */

	if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
		if(errno != EEXIST){
			printf("Can't create shared memory\n");
			exit(-1);
		} else {
			if((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
				printf("Can't find shared memory\n");
				exit(-1);
			}
			is_new = 0;
		}
	}

	if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Can't attach shared memory\n");
		exit(-1);
	}

	/*
		Отличие от программы s06e01a.c только здесь...
	*/
	if (is_new) {
		array[0] = 0;
		array[1] = 1;
		array[2] = 1;
	} else {
		array[1] += 1;
		array[2] += 1;
	}

	printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n", array[0], array[1], array[2]);

	if(shmdt(array) < 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}

	return 0;
}
