#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 10

size_t	checkk(char* buffer, char c)
{
	size_t	z;

	z = 0;
	while (buffer && buffer[z] && buffer[z] != c)
	{/*
		if (buffer[z] == c)
			return (z + 1);*/
		z++;
	}
	if (buffer && buffer[z] == c)
		return (z + 1);
	return (0);
}

char*	ft_alloc(size_t size)
{
	char*	allocat;
	size_t	z;

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

char*	ft_strjoin(char* storage, char* buffer, char c)
{
	char*	new;
	size_t	size;
	size_t	z;
	size_t	y;

	if (!storage)
	{
		size = checkk(buffer, c);
		printf("size_buffer = %zu\n", size);
	}
	else
	{
		size = checkk(buffer, c) + checkk(storage, c) - 1;
		printf("size = %zu\n", size);
	}
	new = ft_alloc(size);
	z = 0;
	y = 0;
	while (size > z)
	{
		if (storage && storage[z])
			new[z] = storage[z];
		else
			new[z] = buffer[y++];
		z++;
	}
	if (storage)
	{
		free(storage);
		storage = NULL;
	}
	return (new);
}

char*	ft_save(int fd, char* storage, size_t *new_line)
{
	char*	buffer;
	ssize_t	len_read;
	size_t	check;

	check = checkk(storage, '\n');
	if (check > 0)
		return (storage);
	buffer = ft_alloc(BUFFER_SIZE);
	len_read = BUFFER_SIZE;
	while (check == 0 && len_read == BUFFER_SIZE)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		storage = ft_strjoin(storage, buffer, '\0');
		check = checkk(storage, '\n');
	}
	printf("check = %zu--------\n", check);
	*new_line = check;
	free(buffer);
	buffer = NULL;
	return (storage);
}

char*	ft_line(char* str)
{
	char*	line;

	line = ft_strjoin(NULL, str, '\n');
	return (line);
}

char*	ft_chyata(char* str)
{
	char*	storage;
	size_t	z;
	size_t	size;

	z = checkk(str, '\n');
	size = z;
	storage = ft_strjoin(NULL, str + z, '\0');
	/*while (str[z])
		z++;
	size = z - size;*/
	free(str);
	str = NULL;
	return (storage);
}

char*	get_next_line(int fd)
{
	static char*	storage;
	static size_t	new_line;
	char*			line;
	char*			str;
/*
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}*/
	printf("new_line = %zu---\n", new_line);
	str = ft_save(fd, storage, &new_line);
	printf("new_line = %zu---------\n", new_line);
	line = ft_line(str);
	storage = ft_chyata(str);
	return (line);
}

int main()
{
	char*	buffer1;
	char*	buffer2;
	char*	buffer3;
	char*	buffer4;
	char*	buffer5;
	char*	buffer6;
	char*	buffer7;
	char*	buffer8;
	int 	fd;

	fd = open("9a7ba", O_RDWR);
	printf("fd = %d\n", fd);
	buffer1 = get_next_line(fd);
	buffer2 = get_next_line(fd);
	buffer3 = get_next_line(fd);
	buffer4 = get_next_line(fd);
	buffer5 = get_next_line(fd);
	buffer6 = get_next_line(fd);
	buffer7 = get_next_line(fd);
	buffer8 = get_next_line(fd);
	printf("------------main-------------\n");
	printf("buffer1 = %s\n", buffer1);
	printf("buffer2 = %s\n", buffer2);
	printf("buffer3 = %s\n", buffer3);
	printf("buffer4 = %s\n", buffer4);
	printf("buffer5 = %s\n", buffer5);
	printf("buffer6 = %s\n", buffer6);
	printf("buffer7 = %s\n", buffer7);
	printf("buffer8 = %s\n", buffer8);
	//while (1);
}
