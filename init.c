#include <stdio.h>
#include <unistd.h>

int main(void)
{
	puts("Hello World");
	fflush(stdout);

	/* Как PID 1 нельзя просто выйти — ядро сделает panic. Ждём. */
	for (;;)
		pause();

	return 0;
}
