#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1

size_t	ft_check(char* buffer, char c)
{
	size_t	z;

	z = 0;
	while (buffer && buffer[z] && buffer[z] != c)
		z++;
	if (buffer && buffer[z] == c)
	{
		if (c == '\0')
			return (z);
		return (z + 1);
	}
	return (0);
}

char*	ft_calloc(size_t size)
{
	char*	allocat;
	size_t	z;

	if (!size)
		return (NULL);
	allocat = (char*)malloc(sizeof(char) * (size + 1));
	if (!allocat)
		return (NULL);
	z = 0;
	while (size >= z)
	{
		allocat[z] = '\0';
		z++;
	}
	return (allocat);
}

void	ft_free(char*	str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
char*	ft_strjoin(char* storage, char* buffer, char c)
{
	char*	new;
	size_t	size;
	size_t	z;
	size_t	y;

	size = ft_check(buffer, c) + ft_check(storage, c);
	new = ft_calloc(size);
	z = 0;
	while (storage && storage[z] && size > z)
	{
		new[z] = storage[z];
		z++;
	}
	ft_free(storage);
	y = 0;
	while (buffer && buffer[y] && size > z + y)
	{
		new[z + y] = buffer[y];
		y++;
	}
	//ft_free(storage);
	return (new);
}

char*	ft_save(int fd, char* storage, ssize_t*	line_read)
{
	char*	buffer;
	size_t	check;

	buffer = ft_calloc(BUFFER_SIZE);
	check = 0;
	while (!check)
	{
		*line_read = read(fd, buffer, BUFFER_SIZE);
		if (!*line_read)
		{
			//ft_free(storage);
			ft_free(buffer);
			return (NULL);
		}
		storage = ft_strjoin(storage, buffer, '\0');
		check = ft_check(storage, '\n');
	}
	ft_free(buffer);	
	return (storage);
}

char*	ft_chyata(char* str)
{
	char*	storage;
	size_t	size;

	size = ft_check(str, '\n');
	storage = ft_strjoin(NULL, str + size, '\0');
	free(str);
	//ft_free(str);
	return (storage);
}

char*	get_next_line(int fd)
{
	char*		line;
	static char*	storage;
	static size_t	line_read;
	static size_t	check;
	size_t		new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free(storage);
		return (NULL);
	}
	new_line = ft_check(storage, '\n');
	if (check && line_read != BUFFER_SIZE)
	{
		ft_free(storage);
		return (NULL);
	}
	if (!new_line)
	{
		storage = ft_save(fd, storage, &line_read);
		check = 1;
	}
	/*if (!line_read)
	{
		ft_free(storage);
		return (NULL);
	}*/
	line = ft_strjoin(storage, NULL, '\n');
	storage = ft_chyata(storage);
	return (line);
}

int main()
{
	char*	buffer;
	int 	fd;
	int	z;

	fd = open("9a7ba", O_RDWR);
	z = 5;
	printf("fd = %d\n", fd);
	while (1)
	{
		buffer = get_next_line(fd);
		printf("buffer_1 = %s\n", buffer);
		if (!buffer)
			break;
	}
	while (z--)
	{
		buffer = get_next_line(fd);
		printf("buffer_2 = %s\n", buffer);
	}
	while (1);
//	system("leaks a.out");
	return (0);
}
