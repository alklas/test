#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
// Создаем массив из двух элементов для хранения файловых дескрипторов для чтения и для записи
	int fd[2];
	size_t size;
	char string[] = "Hello, world!";
	char resstring[14];
	if(pipe(fd) < 0) {
		printf("Не получилось создать pipe()");
//Возврат признака аварийного завершения программы (-1)
		exit(-1);
	}
	size = write(fd[1], string, 14);
//Проверка количества байт, записанных в строку с помощью write()
	if(size != 14) {
		printf("Не получается записать строку\n");
		exit(-1);
	}
	size = read(fd[0], resstring, 14);
//Проверка количества байт, прочитанных из pipe() с помощью read()
	if(size != 14) {
		printf("Не получилось прочитать строку\n");
		exit(-1);
	}
	printf("%s\n", resstring);
//Закрытие pipe для чтения
	if (close(fd[0]) < 0) {
		printf("Не получилось закрыть входящий поток\n");
		exit(-1);
	}
//Закрытие pipe для записи
	if (close(fd[1]) < 0) {
		printf("Не получилось закрыть исходящий поток\n");
		exit(-1);
	}
	return 0;
}
