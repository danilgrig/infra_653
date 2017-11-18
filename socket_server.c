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

#define max_text 1000
#define max_name 100

struct msg_t {
	time_t time;
	char name[max_name];
	char text[max_text];
};

struct user_t {
	char name[max_name];
	int connfd, idx, authorized;
};

struct user_t users[100];
int online_users;


void die(char *msg) {
	printf("error: %s, %s\n", msg, strerror(errno));
	exit(1);
}

void* process_client(void* _arg) {
	int idx = *((int *)_arg);
	int i, j;
	struct msg_t msg;

	printf("started thread %d, connfd=%d\n", idx, users[idx].connfd);

	while (1) {
		printf("size=%d\n", sizeof(msg));
		if (i = recv(users[idx].connfd, &msg, sizeof(msg), 0) < 0) {
			printf("%s disconnected\n", users[idx].name);
			close(users[idx].connfd);
			return NULL;
		}
		printf("i=%d\n", i);
		if (users[idx].authorized == 0) {
			strcpy(users[idx].name, msg.name);
			users[idx].authorized = 1;
		}

		for (i = 0; i < online_users; i++) {
			if (i != idx) {
				j = send(users[i].connfd, &msg, sizeof(msg), MSG_CONFIRM);
				printf("[%s] send %d bytes to %s\n", msg.name, j, users[i].name);
			}
		}
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	online_users = 0;
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

	while (1) {
		if ((users[online_users].connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0) {
			die("can't accept");
		}
		printf("got new connection\n");
		users[online_users].idx = online_users;
		users[online_users].authorized = 0;

		int result = pthread_create(
			&thread_id[online_users],
			(pthread_attr_t *)NULL, 
			process_client,
			&(users[online_users].idx)
		);

		if (result) {
			printf("Can`t create thread, returned value = %d\n", result);
			exit(1);
		}

		online_users++;
		printf("online_users=%d\n", online_users);
	}
}
