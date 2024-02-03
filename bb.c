#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 10

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

char*	get_next_line(int fd)
{
	static char*	storage;
	static size_t	new_line;
	char*			line;
	char*			data;

	/*if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}*/
	if (new_line)
	data = ft_save(fd, storage, &new_line);
	line = ft_line(str);
	storage = ft_chyata(str);
	return (line);
}
