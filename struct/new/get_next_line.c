/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:26:27 by abelechg          #+#    #+#             */
/*   Updated: 2024/02/22 06:36:52 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_for_nline(gnl **head, char *str)
{
	int	z;

	z = 0;
	if (!*head && !str)
		return (-1);
	while (str && str[z] && *head)
	{
		if (str && str[z] == '\n')
		{
			(*head)->nline = (*head)->nline + z + 1;
			return ((*head)->nline);
		}
		z++;
	}
	(*head)->nline += z;
	if ((*head)->lread == -1)
		return ((*head)->nline);
	return (0);
}

gnl	*update_node_save(gnl **head, int index, int *new_line, int *save_line)
{
	gnl	*new;
	gnl	*node;
	int	z;

	*save_line = update_node_size(head, index);
	z = 0;
	new = NULL;
	node = *head;
	if (*save_line <= 0)
	{
		*new_line = 0;
		return (NULL);
	}
	else if (*save_line > 0)
	{
		new = create_new_node(*save_line);
		if ((*head)->lread == -1)
			new->lread = (*head)->lread;
		while (node->storage && node->storage[index + z])
		{
			new->storage[z] = node->storage[index + z];
			z++;
		}
		new->storage[z] = 0;
		clear_linked_list(head);
		*save_line = 0;
	}
	return (new);
}

char	*store_new_line(gnl **head, int *new_line, int *save_line)
{
	gnl		*new;
	char	*line;
	int		index;
	int		y;

	new = *head;
	line = (char *)malloc(sizeof(char) * (*save_line + (*head)->nline + 1));
	y = 0;
	while (new && (*save_line + (*head)->nline) > y)
	{
		index = 0;
		while (new->storage[index] && (*save_line + (*head)->nline) > y)
			line[y++] = new->storage[index++];
		if (*new_line == y)
			break ;
		new = new->next;
	}
	line[y] = 0;
	*head = update_node_save(head, index, &*new_line, &*save_line);
	if (*head)
		*new_line = search_for_nline(head, new->storage);
	return (line);
}

gnl	*read_data(int fd, gnl **head, int *new_line, int *save_line)
{
	gnl		*new;
	ssize_t	line_read;

	while (!*new_line)
	{
		new = NULL;
		new = create_new_node(BUFFER_SIZE);
		line_read = read(fd, new->storage, BUFFER_SIZE);
		if (line_read > 0)
			add_back_node(head, new);
		else
		{
			clear_linked_list(&new);
			if (!*head)
			{
				*save_line = -1;
				return (NULL);
			}
		}
		if (line_read != BUFFER_SIZE)
			(*head)->lread = -1;
		*new_line = search_for_nline(head, new->storage);
	}
	return (*head);
}

char	*get_next_line(int fd)
{
	static gnl		*save_data;
	static int		save_line;
	static int		new_line;
	char			*str_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || save_line == -1)
		return (NULL);
	save_data = read_data(fd, &save_data, &new_line, &save_line);
	if (!save_data)
		return (NULL);
	str_line = store_new_line(&save_data, &new_line, &save_line);
	return (str_line);
}
