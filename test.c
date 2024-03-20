#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char*	ft_strcpy(char* storage, char* buffer, ssize_t len_read)
{
	int		z;

	z = 0;
	while (len_read--)
	{
		printf("buf[%d] = %c | ", z, buffer[z]);
		storage[z] = buffer[z];
		z++;
	}
	printf("\n");
	storage[z] = '\0';
	printf("ss = %s\n", storage);
	return (storage);
}

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
	//if (storage)
	//	free(storage);
	new[y] = '\0';
	printf("alocate = %s\n", new);
	return (new);
}

int     ft_checke(char* buffer, int len_read) // where is new line in buffer
{
	int	z;

	z = 0;
    while (len_read)
    {
		if (buffer[z] == '\n')
			return (z + 1);
        len_read--;
		z++;
    }
    return (0);
}

char*   get_next_line(int fd)
{
	static char*	storage;
	char*			buffer;
	char*			new;
	ssize_t         len_read;
	int				check;
	int				BUFFER_SIZE;
	int				z;

	z = 0;
	BUFFER_SIZE = 15;
    len_read = 15;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (BUFFER_SIZE == len_read)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		buffer[len_read] = '\0';
		storage = ft_allocate(new, buffer, len_read);
		printf("storage_%d = %s\n", z + 1, storage);
		//check = ft_checke(buffer, len_read);
		//printf("check_%d = %d\n", z + 1, check);
		printf("--------------------------------------------\n\n");
		z++;
	}
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
	printf("aaa\n");
	printf("fd = %d\n", fd);
	buffer1 = get_next_line(fd);
	buffer2 = get_next_line(fd);
	buffer3 = get_next_line(fd);
	printf("buffer1 = %s\n", buffer1);
	printf("buffer2 = %s\n", buffer2);
	printf("buffer3 = %s\n", buffer3);
	printf("zzz\n");
}
