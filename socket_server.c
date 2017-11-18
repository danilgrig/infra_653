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

	int connfd;
	if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) < 0) {
		die("can't accept");
	}
	printf("got new connection\n");

}
