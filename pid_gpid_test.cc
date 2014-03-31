#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	if ( -1 == pipe(pipefd) )
	{
		perror("Err pipe");
		exit(-1);
	}

	pid_t fork_pid = fork();
	if ( fork_pid < 0 )
	{
		fprintf(stderr, "Err while fork\n");
		exit(-1);
	}
	else if( fork_pid > 0 )
	{
		pid_t pid = getpid();
		printf("The pid of father proc is [%d]\n", pid);

		pid_t pgid = getpgid(pid); // the same as getpgrp()
		printf("The pgid of father proc is [%d]\n", pgid);

		close(pipefd[1]);

		char buf[50];
		read(pipefd[0],buf,sizeof(buf));

		setpgid(pid, atoi(buf));
		pgid = getpgid(pid); // the same as getpgrp()
		printf("The pgid of father pid after setgpid to child pid is [%d]\n", pgid);

		wait(NULL);
		close(pipefd[0]);
		exit(0);
	}
	else
	{
		pid_t pid = getpid();
		printf("The pid of child proc is [%d]\n", pid);

		pid_t pgid = getpgid(pid); // the same as getpgrp()
		printf("The pgid of child proc is [%d]\n", pgid);

		close(pipefd[0]);

		char buf[50];
		sprintf(buf, "%d", pid);
		write(pipefd[1], buf, strlen(buf));

		close(pipefd[1]);
		exit(0);
	}
}
