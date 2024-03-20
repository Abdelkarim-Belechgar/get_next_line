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



gnl	*update_node_save(gnl **head, int index, int *new_line, int *save_line) // 23
{
	gnl	*new;
	gnl	*node;
	int	z;

	z = 0;
	new = NULL;
	node = *head;
	while (node->next)
		node = node->next;
	if (*save_line > 0)
	{
		new = create_new_node(*save_line);
		new->lread = (*head)->lread;
		while (node->storage && node->storage[index + z])
		{
			new->storage[z] = node->storage[index + z];
			z++;
		}
		new->storage[z] = 0;
		*save_line = 0;
	}
	clear_linked_list(head);
	return (new);
}

char	*store_new_line(gnl **head, int *new_line, int *save_line) // 22
{
	gnl		*new;
	char	*line;
	int		index;
	int		y;

	new = *head;
	line = (char *)malloc(sizeof(char) * (*new_line + 1));
	if (!line)
		return (NULL);
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
	*save_line = update_node_size(&new, index);
	if (!*save_line && *head && (*head)->lread == -1)
		*save_line = -1;
	*head = update_node_save(head, index, &*new_line, &*save_line);
	return (line);
}

gnl	*read_data(int fd, gnl **head, int *new_line, int *save_line) // 24
{
	gnl		*new;

	while (!*new_line)
	{
		new = create_new_node(BUFFER_SIZE);
		if (!new)
			return (NULL);
		*new_line = read(fd, new->storage, BUFFER_SIZE);
		new->storage[*new_line] = 0;
		if (*new_line > 0)
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
		if (*new_line != BUFFER_SIZE)
			(*head)->lread = -1;
		*new_line = search_for_nline(head);
	}
	return (*head);
}

char	*get_next_line(int fd) // 11
{
	static gnl		*save_data;
	static int		new_line;
	static int		save_line;
	char			*str_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || save_line == -1)
		return (NULL);
	new_line = search_for_nline(&save_data);
	save_data = read_data(fd, &save_data, &new_line, &save_line);
	if (!save_data)
		return (NULL);
	str_line = store_new_line(&save_data, &new_line, &save_line);
	return (str_line);
}
