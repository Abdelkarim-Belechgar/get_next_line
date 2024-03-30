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

void	update_data(char **data, size_t flag)
{
	char	*save;
	size_t	size;
	size_t	z;
	
	size = update_size(*data + flag);
	if (!flag)
	{
		clear_string(data);
		return ;
	}
	save = malloc(sizeof(char) * (size + 1));
	if (!save)
	{
		clear_string(data);
		return ;
	}
	z = 0;
	while (size > z)
	{
		save[z] = (*data)[flag + z];
		z++;
	}
	save[z] = 0;
	*data = save;
}

char	*sorte_new_line(char *data, size_t flag)
{
	char	*line;
	size_t	z;

	if (!flag)
		return (NULL);
	line = malloc(sizeof(char) * (flag + 1));
	if (!line)
		return (NULL);
	z = 0;
	while (flag > z)
	{
		line[z] = data[z];
		z++;
	}
	line[z] = 0;
	return (line);
}

char	*read_data(int fd, char **data, size_t *flag, ssize_t size)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		clear_string(data);
		return (NULL);
	}
	while (!size)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == 0)
			break ;
		buffer[size] = 0;
		join_string(data, buffer, *flag, size);
		size = search_for_nline(buffer, flag);

	}
	clear_string(&buffer);
	if (!data || !*data)
		return (NULL);
	buffer = sorte_new_line(*data, *flag);
	if (!buffer)
	{
		clear_string(data);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;
	ssize_t		size;
	size_t		new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		clear_string(&data);
		return (NULL);
	}
	new_line = 0;
	size = search_for_nline(data, &new_line);
	line = read_data(fd, &data, &new_line, size);
	if (!line)
		return (NULL);
	update_data(&data, new_line);
	return (line);
}
