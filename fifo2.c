#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
        int fd;
        size_t size;
        char resstring[11];
        //Создаём сивольный массив, где будет храниться имя файла FIFO
        char name[] = "fifo.fifo";
	if ((fd = open(name, O_RDONLY)) < 0) {
        	printf("Не удалось открыть FIFO для чтения\n");
                exit(-1);
        }
        size = read(fd, resstring, 11);
        if (size != 11) {
                printf("Не удалось прочитать информацию из FIFO\n");
                exit(-1);
        }
        printf("Процесс fifo2 прочитал информацию: %s\n", resstring);
        if (close(fd)<0) {
	        printf("Не получилось закрыть FIFO, открытый на чтение\n");
                exit(-1);
        }
        return 0;
}
