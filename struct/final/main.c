#include "get_next_line.h"

int main(void)
{
	char*	str;
	int		fd;
	int		z = 0;
	
	fd = open("fdnew.txt", O_RDONLY);
	while(1)
	{
		str = get_next_line(fd);
		printf("***str[%d] = %s", z++, str);
		if(!str)
			break;
		free(str);
	}
	// system("leaks a.out");
    return (0);
}