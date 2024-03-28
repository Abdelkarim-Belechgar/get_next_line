#include "get_next_line.h"

int main(void)
{
	char	*str;
	int		fd;

	fd = open("test", O_RDONLY);
	printf("fd = %d\n", fd);
	while (1)
	{
		str = get_next_line(fd);
		printf("%s", str);
		if (!str)
			break ;
		free(str);
	}
}