#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

struct stat st;

int main() {
	
	int content[2], crypted[2], size[2];

	pipe(content);
	pipe(crypted);
	pipe(size);

	if (fork() == 0) { //child
		int sizeOfFile = 0;
		char cont[1000];
		int key = 10;

		close(size[1]);
		close(content[1]);
		close(crypted[0]);

		read(size[0], &sizeOfFile, sizeof(int));
		//printf("%d\n", sizeOfFile);
		int sum = 0;
		while (sum < sizeOfFile){
			sum += read(content[0], cont + sum, sizeof(char) * (sizeOfFile - sum));
		}

		for (int i = 0; i < sizeOfFile; ++i) {
			cont[i] ^= key;
		}

		//printf("%s\n", cont);
		write(crypted[1], cont, sizeof(char) * sizeOfFile);

		close(size[0]);
		close(content[0]);
		close(crypted[1]);


	} else { //parent

		close(size[0]);
		close(content[0]);
		close(crypted[1]);

		char fileName[50], fileContent[1000], fileCont[1000];
		
		scanf("%s", fileName);
		//printf("%s", fileName);

		int f = open(fileName, O_RDONLY);

		stat(fileName, &st);
		//printf("%d\n", (int)(st.st_size));


		write(size[1], &(st.st_size), sizeof(int));
		//fscanf(f, "%s", fileContent);
		read(f, fileContent, sizeof(char) * st.st_size);
		write(content[1], fileContent, sizeof(char) * st.st_size);
		
		//printf("%s", fileCont);

		close(f);
		int sum = 0;
		while(sum < st.st_size) {
			sum += read(crypted[0], fileCont + sum, sizeof(char) * (st.st_size - sum));
		}


		for (int i = 0; i < st.st_size; ++i) {
			printf("%c", fileCont[i]);
		}

		close(size[1]);
		close(content[1]);
		close(crypted[0]);
		wait(0);
	}

	return 0;
}
