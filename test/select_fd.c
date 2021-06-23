#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>

// https://blog.csdn.net/test1280/article/details/94436202

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s fd\n", argv[0]);
		exit(1);
	}

	int fd = atoi(argv[1]);
	if (fd < 3)
	{
		fprintf(stderr, "fd domain: (2, fd_max]\n");
		exit(1);
	}

	fprintf(stdout, "fd max size: %d\n", FD_SETSIZE);

	// 创建指定文件描述符，与标准输入关联
	if (dup2(0, fd) == fd)
	{
		fprintf(stdout, "dup2 ok! new fd: %d\n", fd);
	}
	else
	{
		fprintf(stderr, "dup2 error: %d(%s)\n", errno, strerror(errno));
		exit(1);
	}

	// 设为非阻塞
	long flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags|O_NONBLOCK);

	fprintf(stdout, "will into main loop...\n");

	while (1)
	{
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(fd, &readSet);

		struct timeval tv;
		tv.tv_sec = 3;
		tv.tv_usec = 0;

		int res = select(fd + 1, &readSet, NULL, NULL, &tv);
		if (res == -1) {
			fprintf(stderr, "select error: %d(%s)\n", errno, strerror(errno));
			exit(1);
		} else if (res == 0) {
			fprintf(stdout, "timeout...\n");
		} else {
			static char buff[1024];
			int count = read(fd, buff, sizeof(buff));
			fprintf(stdout, "select return %d, read count %d\n", res, count);
		}
	}

	exit(0);
}
