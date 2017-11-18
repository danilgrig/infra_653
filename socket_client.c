#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>

#define max_text 1000
#define max_name 100

struct msg_t {
	time_t time;
	char name[max_name];
	char text[max_text];
};

void die(char *msg) {
	printf("error: %s, %s\n", msg, strerror(errno));
	exit(1);
}

void* wait_messages(void* _arg) {
	int sockfd = *((int *)_arg);
	int recv_len;
	struct msg_t msg;

	printf("started thread\n");

	while (1) {
		if ((recv_len = recv(sockfd, &msg, sizeof(msg), 0)) <= 0) {
			die("can't recv");
		}

		printf("received %d bytes from %s: %s\n", recv_len, msg.name, msg.text);
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	int sockfd;
	pthread_t thread_id;
	struct msg_t msg;
	struct sockaddr_in serv_addr; 

	if(argc != 3) {
		printf("\n Usage: %s <ip of server> <nickname> \n",argv[0]);
		return 1;
	} 

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		die("can't create socket");
	} 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000); 

	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
		die("inet_pton error occured");
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		die("Connect Failed");
	} 
	int result = pthread_create(
		&thread_id,
		(pthread_attr_t *)NULL, 
		wait_messages,
		&sockfd
	);

	strcpy(msg.name, argv[2]);
	strcpy(msg.text, "i am connected");
	if (send(sockfd, &msg, sizeof(msg), 0) < 0) {
		die("can't send");
	}
	printf("send my name to server\n");

	while (1) {
		scanf("%s", msg.text);
		if (send(sockfd, &msg, sizeof(msg), 0) < 0) {
			die("can't send");
		}
		printf("send msg to server\n");
	}

	return 0;
}
