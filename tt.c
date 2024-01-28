#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char*	ft_allocate(char* storage, char* buffer, ssize_t len_read)
{
	char*	new;
	int		size;
	int		z;
	int		y;

	z = 0;
	y = 0;
	size = 0;
	if (!storage)
		size = len_read;
	else
		size = strlen(storage) + len_read;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	/*while (size--)
	{
		if (storage && storage[y])
			new[y] = storage[y];
		else
		{
			new[y] = buffer[z];
			z++;
		}
		y++;
	}*/
	while (storage && storage[y])
	{
		new[y] = storage[y];
		y++;
	}
	while (buffer[z])
	{
		new[y] = buffer[z];
		z++;
		y++;
	}
	new[y] = '\0';
	if (storage)
		free(storage);
	return (new);
}

int     ft_checke(char* buffer) // where is new line in buffer
{
	int	z;

	z = 0;
    while (buffer && buffer[z])
    {
		if (buffer[z] == '\n')
			return (z + 1);
        z++;
    }
    return (0);
}

char*	ft_ret(char* storage, int check)
{
	char	*new;
	int		z;

	z = 0;
	new = (char *)malloc(sizeof(char) * (check + 1));
	while (check--)
	{
		new[z] = storage[z];
		z++;
	}
	new[z] = '\0';
	return (new);
}

char*   get_next_line(int fd)
{
	static char*	storage;
	char*			buffer;
	ssize_t         len_read;
	int				BUFFER_SIZE;
	int 			check;

	BUFFER_SIZE = 15;
	len_read = 15;
	check = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (check == 0 && len_read == BUFFER_SIZE)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		buffer[len_read] = '\0';
		storage = ft_allocate(storage, buffer, len_read);
		check = ft_checke(storage);
	}
	printf("%d\n", check);
	printf("new = %s\n", ft_ret(storage, check));
	free(buffer);
	return (storage);
}

int main()
{
    int     fd;
	char*	buffer1;
	char*	buffer2;
	char*	buffer3;

    fd = open("9a7ba", O_RDONLY);
	buffer1 = get_next_line(fd);
	buffer2 = get_next_line(fd);
//	buffer3 = get_next_line(fd);
	printf("buffer1 = %s\n", buffer1);
	printf("buffer2 = %s\n", buffer2);
//	printf("buffer3 = %s\n", buffer3);
}
