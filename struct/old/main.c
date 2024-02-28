#include "get_next_line.h"

int main(void)
{
	char*	new;
	int		fd;
	size_t	z;


	z = 0;
	fd = open("test", O_RDONLY);
	printf("fd = %d\n", fd);
	while (1)
	{
	    // printf("================ start %zu ================\n", z + 1);
		new = get_next_line(fd);
		printf("***===new[%zu] = %s===***\n", z + 1, new);
	    printf("================= end %zu =================\n\n\n", z + 1);
		// printf("************************************************************************************\n\n\n");
		if (!new)
			break;
		free(new);
		z++;
	}
    return (0);
}
