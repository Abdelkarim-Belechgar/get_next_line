#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

size_t	ft_strlen(const char* s)
{
	size_t	z;

	z = 0;
	while (s && s[z])
		z++;
	return (z);
}

char*	ft_strjoin(char* save, char* buffer)
{
	char*	new;
	size_t	size;
	size_t	z;
	size_t	y;
	
	z = 0;
	y = 0;
	if (!buffer)
		return (NULL);
	if (!save)
		size = ft_strlen(buffer);
	else
		size = ft_strlen(save) +ft_strlen(buffer);
	printf("size = %zu\n", size);
	new = (char*)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (size > z + y)
	{
		if (save && save[z])
		{
			new[z] = save[z];
			z++;
		}
		else
		{
			new[z + y] = buffer[y];
			y++;
		}
	}
	new[size] = '\0';
	if (save)
		free(save);
	return (new);
}

char*	result(char* save, int check)
{
	char*	new;
	int		z;

	z = 0;
	if (!new)
		return (NULL);
	new = (char*)malloc(sizeof(char) * (check + 1));
	while (check--)
	{
		new[z] = save[z];
		z++;
	}
	new[z] = '\0';
	printf("result = %s\n", new);
	return (new);
}

char*	chyata(char* save, int check)
{
	char*	new;
	int		z;

	z = 0;
	printf("chyata = ");
	while (save[check + z])
	{
		//printf("%c ", save[z]);
		z++;
	}
	printf("\n\n");
	new = (char*)malloc(sizeof(char) * (z + 1));
	z = 0;
	while (save[check + z])
	{
		new[z] = save[check + z];
		z++;
	}
	new[z] = '\0';
	free(save);
	return (new);
}

int ft_check(char* buffer)
{
	size_t	z;

	z = 0;
	while (buffer && buffer[z])
	{
		if (buffer[z] == '\n')
			return (z + 1);
		z++;
	}
	return (0);
}

char*	ft_calloc(size_t size)
{
	char*	new;
	int		z;

	if ((int)size < 0)
		return (NULL);
	new = (char*)malloc(size + 1);
	if (!new)
		return (NULL);
	z = 0;
	while (size > z)
	{
		new[z] = '\0';
		z++;
	}
	return (new);
}

int		ft_line(char* save)
{
	int	z;

	z = 0;
	while (save && *save)
	{
		if (*save == '\n')
			z++;
		save++;
	}
	printf("\n\n\n");
	return (z);
}

char*	get_next_line(int fd)
{
	static char*	save;
	char*			new = NULL;
	static int		line;
	char*			buffer;
	size_t			BUFFER_SIZE;
	static size_t	check;
	ssize_t			lread;

	check = 0;
	BUFFER_SIZE = 1;
	line = ft_line(save);
	if (check > 0)
	{
		printf("ss\n");
		if (new)
			free(new);
		new = result(save, check);
		save = chyata(save, check);
		return (new);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (check == 0)
	{
		lread = read(fd, buffer, BUFFER_SIZE);
		buffer[lread] = '\0';
		save = ft_strjoin(save, buffer);
		printf("saveall = %s\n", save);
		check = ft_check(save);
		printf("check = %zu\n", check);
		line = ft_line(save);
		printf("line 2 = %d\n", line);
		if (check > 0)
		{
			if (new != NULL)
				free(new);
			new = result(save, check);
			printf("new = %s\n", new);
			save = chyata(save, check);
			printf("save = %s\n", save);
		}
	}
	printf("line 3 = %d\n", line);
	free(buffer);
	return (new);
}

int main()
{
	char*	buffer1;
	char*	buffer2;
	char*	buffer3;
	char*	buffer4;
	char*	buffer5;
	int 	fd;

	fd = open("9a7ba", O_RDWR);
	printf("fd = %d\n", fd);
	buffer1 = get_next_line(fd);
	buffer2 = get_next_line(fd);
	buffer3 = get_next_line(fd);
	buffer4 = get_next_line(fd);
	buffer5 = get_next_line(fd);
	printf("------------main-------------\n");
	printf("buffer1 = %s\n", buffer1);
	printf("buffer2 = %s\n", buffer2);
	printf("buffer3 = %s\n", buffer3);
	printf("buffer4 = %s\n", buffer4);
	printf("buffer5 = %s\n", buffer5);
	while (1);
}
