#include "get_next_line.h"

int main(void)
{
	char*	newfd, newfc;
	int		fd, fc;
	size_t	z;
	fd = open("fcnew.txt", O_RDONLY);
	fc = open("fdnew.txt", O_RDONLY);
	z = 0;
	while(1)
	{
		newfd = get_next_line(fd);
		printf("fd = %s", newfd);
		newfc = get_next_line(fc);
		printf("fc = %s", newfc);
		if(newfc == NULL && newfd == NULL)
			break;
		free(newfc);
		free(newfd);
	}
	// system("leaks a.out");
    return (0);
}