#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int a = 0; //Инициализация глобальной статической переменной, доступной из каждого thread'а
//Функция, выполняющаяся в рамках второго thread'а
void *mythread(void *dummy){
	pthread_t mythid; //Идентификатор thread'а - для каждого имеет своё значение
	mythid = pthread_self();
	a = a+1;
	printf("Thread %ld, Результат вычисления a = %d\n", mythid, a); //Печать идентификатора текущего thread'а и значения глобальной переменной
	return NULL;
}

int main() {
	pthread_t thid, mythid;
	int result;
	result = pthread_create(&thid, (pthread_attr_t *)NULL, mythread, NULL); //Создание нового thread'а при помощи вызова функции mythread()
	if(result != 0) {
		printf("Ошибка при создании нового thread\'а, возвращенное значение = %d\n", result);
		exit(-1);
	}
	printf("Thread создан, thid = %ld\n", thid);
	mythid = pthread_self(); //Сохраняем в перемнной mythid идентификатор главного thread'а
	a = a+1;
	printf("Thread %ld, Результат вычисления a = %d\n", mythid, a);
	pthread_join(thid, (void **)NULL); //ожидание завершения порожденного thread'а
	return 0;
}
