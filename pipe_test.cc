#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>

#define PERR(name)\
 ( printf("Err func[%s], errno[%d], Err Msg[%s]\n", #name, errno, strerror(errno)) )

int main(int argc, char *argv[])
{
	pid_t pid;
	int pipefd[2];
	char r_buf[1024], w_buf[1024];
	char flag = 0;
	memset(r_buf,0,sizeof(r_buf)*sizeof(char));
	memset(w_buf,0,sizeof(w_buf)*sizeof(char));

	if( -1 == pipe(pipefd) )
	{
		PERR(pipe);
		exit(0);
	}

	pid = fork();

	if(-1 == pid)
	{
		PERR(fork);
		exit(-1);
	}
	else if(0 == pid) // child process
	{
		if( -1 == close(pipefd[1]) ) // close child proc's write fd
		{
			PERR(close);
			exit(-1);
		}
		while( 0 < read(pipefd[0], r_buf, 1024) )
		{
			printf("child proc read from pipe:%s\n", r_buf);
		}
		close(pipefd[0]);
		exit(0);
	}
	else
	{

		scanf("%s",w_buf);
		if( close(pipefd[0]) == -1 )
		{
			PERR(close);
			exit(0);
		}
		while( EOF != scanf("%s",w_buf) )
		{
			write(pipefd[1], w_buf, strlen(w_buf)+1); //bug1, not add \0 here
			printf("father proc write to pipe:%s\n", w_buf);
			sleep(2); // wait for child proc to exit

			// exit(0); // bug2, exit father proc without waiting the child proc to exit, thus the child proc will be an zombie proc.
		}

		close(pipefd[1]);
		waitpid(pid, NULL, 0); // exit the zombie
		exit(0);

	}

	return 0;
}
