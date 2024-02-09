#include "get_next_line.h"

int	main()
{
	char	*buffer;
	int	fd;
	int	z;

	fd = open("test", O_RDONLY);
	z = 0;
	while (1)
	{
		printf("----------fd = %d----------\n");
		buffer = get_next_line(fd);
		printf("buffer[%d] = %s", z, buffer);
		if (buffer)
			ft_free();
		else
			break;
		z++;
	}
	return (0);
}
