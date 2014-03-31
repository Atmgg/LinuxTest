#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#define file_num 2

int main(int argc, char *argv[])
{
	int fd[file_num];
	fd[0] = open("input_file1",O_RDONLY);
	fd[1] = open("input_file2",O_RDONLY);
	for(int i=0; i<file_num; ++i)
	{
		if(-1 == fd[i])
		{
			perror("open Err");
			exit(-1);
		}
	}

	struct stat stat_arr[file_num];
	
	int ret = 0;
	for(int i=0; i<file_num; ++i)
		ret |= fstat(fd[i], &stat_arr[i]);

	if(ret)
	{
		perror("fstat Err");
		exit(-1);
	}

	size_t size = 0;
	char *buf[file_num];
	struct iovec vec[file_num];

	for(int i=0; i<file_num; ++i)
	{
		if ( stat_arr[i].st_mode & S_IRUSR )
		{
			size = stat_arr[i].st_size+1;
			buf[i] = (char *)malloc(size);
			if(NULL == buf[i])
			{
				fprintf(stderr, "Err while alloc memory\n");
				exit(-1);
			}

			read(fd[i], buf[i], stat_arr[i].st_size);
			buf[i][size] = '\0';

			vec[i].iov_base = buf[i];
			vec[i].iov_len  = size;
		}
		else
		{
			fprintf(stderr, "Err: the %d' file has no authrity\n", i);
			exit(-1);
		}
	}

	if ( -1 == writev(STDOUT_FILENO, vec, file_num) )
	{
		perror("Err writev");
		exit(-1);
	}
	

	for(int i=0; i<file_num; ++i)
	{
		if( buf[i] )
		{
			free(buf[i]);
			buf[i] = NULL;
		}
	}

	exit(0);
}
