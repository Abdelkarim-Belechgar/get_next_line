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

t_line	*update_node(t_line **head, int index, int save_line)
{
	t_line	*new;
	t_line	*node;
	int		z;

	z = 0;
	new = NULL;
	node = *head;
	while (node->next)
		node = node->next;
	if (save_line > 0)
	{
		new = create_new_node(save_line);
		new->lread = (*head)->lread;
		while (node->storage && node->storage[index + z])
		{
			new->storage[z] = node->storage[index + z];
			z++;
		}
		new->storage[z] = 0;
		save_line = 0;
	}
	clear_linked_list(head);
	return (new);
}

char	*store_new_line(t_line **head, ssize_t new_line, int save_line)
{
	t_line	*new;
	char	*line;
	int		index;
	int		z;

	new = *head;
	line = (char *)malloc(sizeof(char) * (new_line + 1));
	if (!line)
		return (NULL);
	z = 0;
	while (new && (new_line > z))
	{
		index = 0;
		while (new->storage[index] && (save_line + (*head)->nline) > z)
			line[z++] = new->storage[index++];
		if (new_line == z)
			break ;
		new = new->next;
	}
	line[z] = 0;
	save_line = save_node_size(&new, index);
	*head = update_node(head, index, save_line);
	return (line);
}

t_line	*read_data(int fd, t_line **head, ssize_t *new_line)
{
	t_line	*new;

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
				return (NULL);
		}
		(*head)->lread = *new_line;
		*new_line = search_for_nline(head);
	}
	return (*head);
}

char	*get_next_line(int fd)
{
	static t_line	*save_data;
	char			*str_line;
	ssize_t			new_line;
	int				save_line;

	new_line = 0;
	save_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		clear_linked_list(&save_data);
		return (NULL);
	}
	new_line = search_for_nline(&save_data);
	save_data = read_data(fd, &save_data, &new_line);
	if (!save_data)
		return (NULL);
	str_line = store_new_line(&save_data, new_line, save_line);
	return (str_line);
}
