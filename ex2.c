#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t   pid1, pid2, pid3;

	pid1 = fork();
	if (pid1 != 0) {
		pid2 = fork();
		if (pid2 != 0) {
			printf("%d diz: sou o pai, meu pai é %d e meus filhos são %d e %d\n", getpid(), getppid(), pid1, pid2);
		}
		else {
			pid3 = fork();
			if (pid3 != 0) {
				printf("%d diz: sou o filho 2, meu pai é %d (pai) e meu filho é %d\n", getpid(), getppid(), pid3);
			}
			else {
				printf("%d diz: sou o filho 4, meu pai é %d (filho 2) e não devo ter filhos\n", getpid(), getppid());
			}
		}
	}
	else {
		pid2 = fork();
		if (pid2 != 0) {
			printf("%d diz: sou o filho 1, meu pai é %d (pai) e meu filho é %d\n", getpid(), getppid(), pid2);
		}
		else {
			pid3 = fork();
			if (pid3 != 0) {
				printf("%d diz: sou o filho 3, meu pai é %d (filho 1) e meu filho é %d\n", getpid(), getppid(), pid3);
			}
			else {
				printf("%d diz: sou o filho 5, meu pai é %d (filho 3) e não devo ter filhos\n", getpid(), getppid());
			}
		}
	}

   return(0);
}
