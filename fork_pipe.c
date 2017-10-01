#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//test

//#define DEBUG_ON
#if defined(DEBUG_ON)
	#define DEBUG(format, args...) printf("LINE %d: " format, __LINE__, args)
#else
	#define DEBUG(format, args...) {}
#endif


int main(int argc, char **argv) {
	if (argc < 4) {
		printf("Usage: %s n l r\n", argv[0]);
		exit(1);
	}
	int n = atoi(argv[1]);
	int l = atoi(argv[2]);
	int r = atoi(argv[3]);
	int d = (r - l + n - 1) / n;
	int *pipes = (int*)malloc(2 * n * sizeof(int));
	int i = 0;
	pid_t p;

	while (l < r) {
		if (pipe(&pipes[2 * i]) == -1) {
			printf("pipe failed\n");
			exit(1);
		}
		p = fork();
		if (p < 0) {
			printf("fork failed\n");
			exit(1);
		} else if (p == 0) {
			int j;
			for (j = 0; j <= 2 * i; j++)
				close(pipes[j]);

			long long s = 0;
			for (j = l; j < r && j < (l + d); j++) {
				s += j;
			}
			char buf[20];
			sprintf(buf, "%lld", s);
			write(pipes[2 * i + 1], buf, strlen(buf) + 1);
			exit(0);
		} else {
			close(pipes[2 * i + 1]);
			printf("pid %d started\n", p);
		}

		i++;
		l += d;
	}
	if (i < n) {
		printf("warn: seems n > r -l\n");
		n = i;
	}

	while ((p = waitpid(-1, 0, 0)) > 0) {
		printf("pid %d finished\n", p);
	}

	long long s = 0;
	for (i = 0; i < n; i++) {
		char buf[20];
		int len;
		len = read(pipes[2 * i], buf, 20);
		buf[len] = 0;
		s += atoll(buf);
	}
	printf("%lld\n", s);

	return 0;
}
