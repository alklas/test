#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	// Создаем массив из двух элементов для хранения файловых дескрипторов для чтения и для записи
	int fd1[2], fd2[2];
	pid_t result;
	size_t size;
	char string1[] = "Hello, child!", string2[] = "Hello, parent!";
	char resstring1[13], resstring2[14];
	if (pipe(fd1) < 0) {
		printf("Не получилось создать pipe()");
	//Возврат признака аварийного завершения программы (-1)
		exit(-1);
	}
	if (pipe(fd2) < 0) {
		printf("Не получилось создать pipe()");
	//Возврат признака аварийного завершения программы (-1)
		exit(-1);
	}
	result = fork();
	if (result<0) {
		printf("Ошибка выполнения fork()\n");
		exit(-1);
	}
	else if (result>0) {
		if (close(fd1[0])<0) {
			printf("Ошибка при закрытии pipe на чтение\n");
			exit(-1);
		}
		if (close(fd2[1])<0) {
			printf("Ошибка при закрытии pipe на запись\n");
			exit(-1);
		}
		size = write(fd1[1], string1, 13);
		//Проверка количества байт, записанных в строку с помощью write()
		if(size != 13) {
			printf("Не получается записать строку\n");
			exit(-1);
		}
		printf("Процесс-родитель записал информацию в pipe\n");
		size = read(fd2[0], resstring2, 14);
		//Проверка количества байт, прочитанных из pipe() с помощью read()
		if(size != 14) {
			printf("Не получилось прочитать строку\n");
			exit(-1);
		}
		printf("Информация от дочернего процесса:");
		for (int i=0; i<14; i++) printf("%c", resstring2[i]);
		printf("\n");
		if(close(fd1[1]) < 0) {
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
		if(close(fd2[0]) < 0) {
			printf("Не получилось закрыть входящий поток\n");
			exit(-1);
		}
	}
	else {
		//Закрытие pipe для записи
		if (close(fd1[1]) < 0) {
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
		if (close(fd2[0]) < 0) {
			printf("Не получилось закрыть входящий поток\n");
			exit(-1);
		}
		size = write(fd2[1], string2, 14);
		//Проверка количества байт, записанных в строку с помощью write()
		if(size != 14) {
			printf("Не получается записать строку\n");
			exit(-1);
		}
		printf("Процесс-ребёнок записал информацию в pipe\n");
		size = read(fd1[0], resstring1, 13);
		//Проверка количества байт, прочитанных из pipe() с помощью read()
		if(size != 13) {
			printf("Не получилось прочитать строку\n");
			exit(-1);
		}
		printf("Информация от родителя:");
		for (int i=0; i<13; i++) printf("%c", resstring1[i]);
		printf("\n");
		//Закрытие pipe для чтения
		if (close(fd1[0]) < 0) {
			printf("Не получилось закрыть входящий поток\n");
			exit(-1);
		}
		if (close(fd2[1]) < 0) {
			printf("Не получилось закрыть исходящий поток\n");
			exit(-1);
		}
	}
	return 0;
}
