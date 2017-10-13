/* Программа для иллюстрации работы с семофорами */

/* Программа получает доступ к одному системному семофору.
   Ждет, пока его значение не станет больше или равным 1
   после запусков программы semaphore_b.c, а затем уменьшает его
   на 1 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int semid; /* IPC-дескриптор для массива IPC семафоров */

	key_t key = 124; /* IPC ключ */

	struct sembuf mybuf; /* Структура для задания операции над семафором */

	/* Пытаемся получить доступ по ключу к массиву семафоров, если он существует,
	   или создать его из одного семафора, если его ещё не существует, с правами
	   доступа rw для всех пользователей */

	if ((semid = semget(key , 2, 0666 | IPC_CREAT)) < 0) {
		printf("Can`t get semid\n");
		exit(-1);
	}

	/* Выполним операцию D(semid , 1) для нашего массива семафоров. Для этого
	сначала заполним структуру mybuf */

	mybuf.sem_op = -1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 1;

	if (semop(semid , &mybuf , 1) < 0) {
		printf("Can`t wait for condition\n");
		exit(-1);
	}

	printf("Condition is present\n");
	return 0;
}

/*
	Удаление семафора:
	ipcs
	ipcrm sem <ipc id>	
*/

