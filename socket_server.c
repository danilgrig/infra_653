#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>


/*
	Финальное задание, сделать чат.
	Программы socket_server.c и socket_client.c демонстрируют работу с сокетом,
	как запустить сервер на определенном порту, послать сообщение, принять сообщение.

	Для начала советую почитать в инете или man-е про эти функции и про то, как вообще работает интернет.

	Как должно работать:
	1) запускается сервер на каком-то компьютере
	2) на любом другом компе запускается клиент, указывает свой логин и адрес сервера
	3) устанавливается соединение, информация о том, что такой-то клиент зашел в систему рассылается всем
	4) каждое сообщение клиента ретранслируется сервером всем остальным клиентам
	5) при первом заходе клиента его просят придумать пароль, который затем сохраняется на сервере (подумать как), при следующих заходах ему надо будет ввести тот же самый пароль
	6) на сервере хранится история всех сообщение. При подключении клиента ему подгражается последняя история
	7) подумать над визуальным удобством чата. Как минимум хочется разделить окошко ввода нового сообщение и поле с перепиской

	Советы:
	1) делайте максимум дебаг-сообщений
	2) проверяйте после каждого системного вызова код ошибки. Сетевые соединения очень не надежны

	Оценивание:
	Всего до этой задачи было 5 задач, каждая по баллу. Ценность этой задачи около 5-ти баллов. Сумма баллов и есть оценка за семестр.
	Если чат получится очень красивым, интересным, будет проявлена самостоятельность решения, то можно получить и больше 5-ти баллов за одну эту задачу.
	То есть, если сделаны все остальные задачи, до для получения Отл вам достаточно сделать только чат в базовой версии (без пунктов 5-7). 
	Если предыдущие задачи сданы не все, то для Отл необходимо сделать какие-то из доп. пунктов.
*/


void die(char *msg) {
	printf("error: %s, %s\n", msg, strerror(errno));
	exit(1);
}

int main(int argc, char *argv[]) {
	int listenfd;
	struct sockaddr_in serv_addr;
	pthread_t thread_id[1000];

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		die("can't create socket");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000); 

	if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		die("can't bind");
	}
	if (listen(listenfd, 10) < 0) {
		die("can't listen");
	}
	printf("server was started\n");

	int connfd;
	if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0) {
		die("can't accept");
	}
	printf("got new connection\n");

	char s[100];
	printf("waiting for a message ...\n");
	int i;
       	i = recv(connfd, s, 10, 0);

	printf("recv %d chars, %s\n", i, s);

	return 0;
}
