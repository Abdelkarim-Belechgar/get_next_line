/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 05:05:07 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/28 05:05:56 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_string(char **storage, char *buffer, ssize_t *size_flag, ssize_t *size_line)
{
	char	*save;
	char	*tmp;
	ssize_t	z;

	printf("size = %lu", *size_flag + *size_line);
	save = (char *)malloc(sizeof(char) * (*size_flag + *size_line + 1));
	if (!save)
	{
		if (storage && *storage)
			clear_string(storage);
		return (NULL);
	}
	z = 0;
	printf("save_flag = %zu\n", *size_flag);
	tmp = *storage;
	while (z < *size_flag + *size_line)
	{
		if (z < *size_flag)
			save[z] = tmp[z];
		else
			save[z] = buffer[z];
		z++;
	}
	save[z] = 0;
	printf("**ss = %s**\n", save);
	clear_string(storage);
	return (save);
}

char	*read_data(int fd, char **storage, ssize_t *size_flag, ssize_t *size_line)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		if (!*size_flag)
			clear_string(storage);
		return (NULL);
	}
	while (!*size_line)
	{
		*size_line = read(fd, buffer, BUFFER_SIZE);
		buffer[*size_line] = 0;
		printf("buffer = *%s*\n", buffer);
		if (*size_line != BUFFER_SIZE)
			break ;
		*storage = join_string(storage, buffer, size_flag, size_line);
		*size_line = search_for_nline(buffer, size_flag);
	}
	printf("hell\n");
	clear_string(&buffer);
	return (*storage);
}

char    *get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	ssize_t		size_flag;
	ssize_t		size_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		clear_string(&storage);
		return (NULL);
	}
	size_flag = 0;
	size_line = search_for_nline(storage, &size_flag);
	line = read_data(fd, &storage, &size_flag, &size_line);
	if (!line)
		return (NULL);
	printf("***%s***\n", line);
	return (line);
}
