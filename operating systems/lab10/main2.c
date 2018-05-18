#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int n;

	printf("Trying to open fifo\n");
	
	int fd = open("./fifo", O_RDONLY);

	if (fd < 0) {
		perror("Eroare deschidere fifo\n");
		exit(2);
	}

	if (read(fd, &n, sizeof(int)) < 0) {
		perror("Eroare citire n\n");
		exit(3);
	}

	for (int i = 0; i < n; ++i) {
		int e;
		if (read(fd, &e, sizeof(int)) < 0) {
			perror("Eroare citire element\n");
			exit(4);
		}
		printf("e:%d\n", e);
	}
	close(fd);
	return 0;
}
