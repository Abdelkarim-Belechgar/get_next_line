/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 06:55:57 by abelechg          #+#    #+#             */
/*   Updated: 2024/01/22 22:09:57 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
/*
char	*ft_strjoin(char *s1, char *s2)
{
	while ()
}
*/
int	find(char	*buffer, int n)
{
	char	*buf;

	if (!buffer)
		return (0);
	buf = buffer;
	while (buf && *buf != '\n' && n--)
		buf++;
	if (*buf == '\n')
		return (1);
	return (0);
}

char	*ft_string(char *new, char *buf, ssize_t n)
{
	char	*buffer;
	int		z;
	int		y;

	//ps
	//lsof -p 22
	if (buf)
	{
		buffer = (char *)malloc(sizeof(char) * (n + 1));
		y = 0;
	}
	else
	{
		buffer = (char *)malloc(sizeof(char) * (strlen(new) + n + 1));
		y = strlen(new);
	}
	z = 0;
	while (n)
	{
		//printf("buf[%d] = %c\t", z, buf[z]);
		if (buf[z] != '\n')
		{
			buffer[z] = buf[z + y];
			n--;
		}
		else
		{
			y++;
			buffer[z] = buf[z + y];
		}
		z++;
	}
	printf("z = %d\n", z);
	buffer[z] = '\0';
	printf("buffern = %s\n", buffer);
	return (buffer);
}
char *get_next_line(int fd)
{
	int		count;
	char	*buffer;
	char	*new;
	int		z;
	int		y;
	ssize_t	n;
	ssize_t	m;

	m = 30;
	n = 30;
	y = 0;
	new = NULL;
	while (n >= m)
	{
		n = read(fd, buffer, n);
		z = find(buffer, n);
		//printf("z find = %d\n", z);
		//printf("buffer = %s\n", buffer);
		new = ft_string(new, buffer, n);
		printf("new[%d] = %s\n", y, new);
		//printf("n read = %zu\n\n", n);
		y++;
	}
	//new = strdup(buffer);
	return (new);
}

int main()
{
	int fd;
	char *buffer;

	fd = open("9a7ba", O_RDONLY);
	buffer = get_next_line(fd);
	return (0);
}
