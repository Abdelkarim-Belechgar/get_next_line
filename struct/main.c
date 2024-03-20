#include "get_next_line.h"


int main(void)
{
	char*	new;
	int		fd;
	size_t	z;
	fd = open("test", O_RDONLY);
	z = 0;
	while (1)
	{
		printf("================ start %zu ================\n", z + 1);
		new = get_next_line(fd);
		// printf("%s", new);
		printf("***===new[%zu] = %s===***\n", z + 1, new);
	    printf("================= end %zu =================\n\n\n", z + 1);
		printf("************************************************************************************\n\n\n");
		if (!new)
			break ;
		free(new);
		z++;
	}
    return (0);
}