#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
	int i;
	printf("Количество аргументов: %d\n\n", argc);
	for (i=0; i<argc; i++) {
		printf("Аргумент %d: %s\n", i, argv[i]);
	}
	printf("\n");
	i=0;
	while (envp[i]!=NULL) {
		printf("%s\n", envp[i]);
		i++;
	}
	return 0;
}
