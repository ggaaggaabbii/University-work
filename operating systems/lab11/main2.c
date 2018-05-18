#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/*
2) Sa se scrie un program care citeste o propozitie de la tastatura formata din cel putin 6 cuvinte, creeaza 5 thread-uri care primesc 
ca si parametru acea propozitie. Fiecare thread va lua un cuvant din propozitie, si il va pune pe o noua pozitie astfel incat dupa ce 
fiecare thread isi incheie executia, propozitia este complet inversata. Thread-ul principal va afisa rezultatul.
Exemplu: Ana are multe mere foarte frumoase -> frumoase foarte mere multe are ana
*/

char str[1000];

int main() {
	
	gets(str);

	printf("%s\n", str);
	return 0;
}
