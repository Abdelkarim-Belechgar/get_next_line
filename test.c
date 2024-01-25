#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char*	ft_strcpy(char* storage, char* buffer, ssize_t len_read)
{
	int		z;
	//char*	new;

	z = 0;
	//printf("buffer strcpy = %s\n", buffer);
	//if ()
	//neiw = *storage;

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

char*	ft_allocate(char* storage, char** buffer, ssize_t len_read)
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
	while (storage[y])
	{
		new[y] = storage[y];
		y++;
	}
	while (size > z)
	{
		new[y] = (*buffer)[z];
		z++;
		y++;
	}
	new[z] = '\0';
	if (storage)
	{
		free(storage);
	}
	printf("alocate = %s\n", new);
	return (new);
}


/**
 * if ft_check = 0 --> not find new line
 * if ft_check = 5 and buffer size = 35 --> 30 index + new line --> 31 character;
 *
 */
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
	ssize_t         len_read;
	int				check;
	int				BUFFER_SIZE;
	int				z;

	z = 0;
	BUFFER_SIZE = 15;
    len_read = 15;
	storage = NULL;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (BUFFER_SIZE == len_read)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		buffer[len_read] = '\0';
		storage = ft_allocate(storage, &buffer, len_read);

		check = ft_checke(buffer, len_read);



		/*printf("check new line = %d\n", check);
		if (!storage)
		{
			printf("aaa	buffer = %s\n", buffer);
			storage = ft_allocate(storage, &buffer, len_read);
			printf("storage allocate = %s\n", storage);
		}
		else
			storage = buffer;
		//storage = ft_allocat(storage, buffer, len_read);
		printf("storage = %s\n\n", storage);
*/
		printf("--------------------------------------------\n");
	}
	return (buffer);
}

int main()
{
    int     fd;
	char*	buffer1;
	char*	buffer2;
	char*	buffer3;

    fd = open("9a7ba", O_RDONLY);
	printf("aaa\n");
	buffer1 = get_next_line(fd);
	buffer2 = get_next_line(fd);
	buffer3 = get_next_line(fd);
	printf("buffer1 = %s\n", buffer1);
	printf("buffer2 = %s\n", buffer2);
	printf("buffer3 = %s\n", buffer3);
	printf("zzz\n");
}
