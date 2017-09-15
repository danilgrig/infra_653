#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//#define DEBUG_ON
#if defined(DEBUG_ON)
	#define DEBUG(format, args...) printf("LINE %d: " format, __LINE__, args)
#else
	#define DEBUG(format, args...) {}
#endif

#define MAX_WORDS 10
#define MAX_CHARS 100

int main() {
	char **s;
	s = (char**) malloc(MAX_WORDS * sizeof(char*));
	s[0] = (char*) malloc(MAX_CHARS);
	char c;
	int i = 0, j = 0, z;
	pid_t p;

	while (scanf("%c", &c) != EOF) {
		DEBUG("c=%c\ti=%d\tj=%d\n", c, i, j);

		if (c == '\n') {
			p = fork();
			if (p < 0) {
				printf("can't fork\n");
				exit(1);
			} else if (p == 0) {
				// child
				s[j][i] = 0;
				for (z = 0; z <= j; z++)
					DEBUG("%s\n", s[z]);

				s[j + 1] = NULL;
				execvp(s[0], (char**)s);
				printf("exec error: %s\n", strerror(errno));
				exit(1);
			} else {
				//main process, free used memory
				i = 0;
				while (j > 0) {
					free(s[j]);
					j--;
				}
			}
		} else if (c == ' ') {
			s[j][i] = 0;
			j++;
			i = 0;
			s[j] = (char*) malloc(MAX_CHARS);
		} else {
			s[j][i] = c;
			i++;
		}
	}

	while ((p = waitpid(-1, 0, 0)) > 0) {
		printf("pid %d finished\n", p);
	}
	printf("all childs have finished, so i too\n");

	return 0;
}
