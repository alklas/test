#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int a = 0;
void *mythread(void *dummy){
	pthread_t mythid;
	mythid = pthread_self();
	a = a+1;
	printf("Thread %ld, Результат вычисления a = %d\n", mythid, a);
	return NULL;
}

int main() {
	pthread_t thid, mythid;
	int result;
	result = pthread_create(&thid, (pthread_attr_t *)NULL, mythread, NULL);
	if(result != 0) {
		printf("Ошибка при создании нового thread\'а, возвращенное значение = %d\n", result);
		exit(-1);
	}
	printf("Thread создан, thid = %ld\n", thid);
	mythid = pthread_self();
	a = a+1;
	printf("Thread %ld, Результат вычисления a = %d\n", mythid, a);
	pthread_join(thid, (void **)NULL);
	return 0;
}
