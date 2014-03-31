#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	/*********************************dup test**************************/
	int fd = dup(STDOUT_FILENO);
	if(-1 == fd)
	{
		perror("dup Err");
		exit(-1);
	}
	char buf[100];
	read( STDIN_FILENO, buf, sizeof(buf)*sizeof(char) );
	write( fd,buf,strlen(buf)+1 );

	/*********************************dup22 test**************************/
	int fd2 = open("std_redc_file", O_RDWR|O_CREAT|O_APPEND, 644);
	if(-1 == fd2)
	{
		perror("fopen Err");
		exit(-1);
	}
	if( -1 == dup2(fd2, STDOUT_FILENO) )
	{
		perror("dup2 Err");
		exit(-1);
	}
	printf("dup2 test\n");

	int StdOutFd = fileno(stdout);
	printf("is StdOutFd == STDOUT_FILENO:%s\n", StdOutFd == STDOUT_FILENO? "Yes": "No");

	exit(0);
}
