/*my_shell.c*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	//char argv[10][10];
	//memset(argv, 0, sizeof(argv));
	char *argv[] = {"ls", NULL};
	char *envp[] = {"PATH=/BIN:/usr/bin", "TERM=console", NULL};
	extern char **environ;
	

	pid_t pid;

	pid = fork();
	if(pid<0)
	{
		perror("fork failed");
		exit(1);
	}
	if(pid==0)
	{
		printf("this is child running\n");
		sleep(3);
		//execve(argv[0], argv, envp);
		execvp(argv[0], argv);
		perror("execvp error\n");
		exit(1);
	}
	else
	{
		int stat_val;
		printf("this is parent running\n");
		waitpid(pid, &stat_val, 0);
		if(WIFEXITED(stat_val))
			printf("child exited with code %d\n",WEXITSTATUS(stat_val));
		else if(WIFSIGNALED(stat_val))
			printf("child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
	}

	return 0;
}












