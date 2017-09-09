#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
	char **s;
	s = (char**) malloc(10);
	s[0] = (char*) malloc(100);
	s[1] = (char*) malloc(100);
	strcpy(s[0], "ls");
	strcpy(s[1], "-al");

	execvp(s[0], (char**)s);
	printf("exec: %s\n", strerror(errno));

	return 0;
}

