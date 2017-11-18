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

	if (send(sockfd, &msg, sizeof(msg), 0) < 0) {
		die("can't send");
	}
	printf("send my name to server\n");

	return 0;
}
