#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	if (mkfifo("./fifo", 0600) < 0) {
		perror("Eroare creare fifo\n");
		exit(1);
	}
	
	int n;
	
	printf("Dati n:");
	scanf("%d", &n);
	printf("Trying to open fifo\n");
	
	int fd = open("./fifo", O_WRONLY);

	if (fd < 0) {
		perror("Eroare deschidere fifo\n");
		exit(2);
	}

	if (write(fd, &n, sizeof(int)) < 0) {
		perror("Eroare trimitere n\n");
		exit(3);
	}

	for (int i = 0; i < n; ++i) {
		int e = rand() % 11 + 10;
		if (write(fd, &e, sizeof(int)) < 0) {
			perror("Eroare trimitere element\n");
			exit(4);
		}
	}
	close(fd);
	unlink("./fifo");
	return 0;
}
