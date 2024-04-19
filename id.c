//Подключение библиотек
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//Главная функция программы
int main() {
// Объявление переменных
	uid_t userid;
	gid_t groupid;
//Системный вызов getuid()
	userid = getuid();
//Системный вызов getgid()
	groupid = getgid();
	printf("Ид. пользователя: %d\n", userid); //Вызов функции printf()
	printf("Ид. группы пользователя: %d\n", groupid);
//Возврат значения "0" из главной функции
	return 0;
}
