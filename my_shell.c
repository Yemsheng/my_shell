/*my_shell.c*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
	//char argv[10][10];
	//memset(argv, 0, sizeof(argv));
	char *argv[] = {"ls","-l", "-R", NULL};
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
		int fd;
		printf("this is child running\n");
		sleep(1);
		//execve(argv[0], argv, envp);
		fd = open("file1", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
		if(fd<0)
		{
			perror("open\n");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
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












