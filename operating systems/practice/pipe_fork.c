#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	
	int shared[2], result[2];
	pipe(shared);
	pipe(result);

	if (fork() == 0) {//child
		int num1, num2;
		close(result[0]);
		close(shared[1]);

		read(shared[0], &num1, sizeof(int));
		read(shared[0], &num2, sizeof(int));
		num1 += num2;
		write(result[1], &num1, sizeof(int));
	
		close(shared[0]);
		close(result[1]);
		exit(0);
	} else {
		int num1 = 3, num2 = 2;
		close(result[1]);
		close(shared[0]);

		write(shared[1], &num1, sizeof(int));
		write(shared[1], &num2, sizeof(int));
		read(result[0], &num1, sizeof(int));

		close(result[0]);
		close(shared[1]);
		printf("%d\n", num1);
	}

	wait(0);
	return 0;
}
