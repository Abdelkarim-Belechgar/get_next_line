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

int	ft_lstcherch(get_ln** head)
{
	get_ln*	new;
	size_t		z;
	int			check;
	int			res;

	res = 0;
	check = 0;
	new = *head;
	while (new)
	{
		z = 0;
		while (new->storage && new->storage[z] && new->storage[z] != '\n')
			z++;
		check += z;
		if (new->storage && new->storage[z] == '\n')
			return (check + 1);
		if (*head && !new->next && *(*head)->lread == -1)
			res = check;
		new = new->next;
	}
	return (res);
}

char*	ft_line(get_ln** head, int* new_line, int* save_line)
{
	get_ln*	new;
	char*		line;
	int			size;
	int			y;
	int			z;

	new = *head;
	size = *new_line;
	line = ft_calloc(size);
	y = 0;
	while (size > y)
	{
		z = 0;
		while (new && new->storage[z] && size > y)
			line[y++] = new->storage[z++];
		if (!new)
			break;
		new = new->next;
	}
	*save_line = ft_lstsize(head, &size);
	if (*save_line == 0)
		ft_lstclear(head);
	return (line);
}

get_ln*	ft_data(get_ln** head, int* save_line, int* new_line)
{
	get_ln*	new;
	get_ln*	list;
	int		    y;
	int			z;
	int		    x;
    
	new = ft_lstnew(*save_line);
	y = 0;
	x = 0;
	list = *head;
	while (list)
	{
		z = 0;
		while (list && list->storage[z])
		{
			if (*new_line <= y + z && *save_line > x)
				new->storage[x++] = list->storage[z++];
			else
				z++;
		}
		y += z;
		list = list->next;
	}
	*new_line = ft_lstcherch(&new);
	ft_lstclear(head);
	return (new);
}

get_ln*	ft_read(int fd, get_ln** head, int* new_line, int* save_line)
{
	get_ln*	new;
	ssize_t		line_read;

	while (!*head || !*new_line)
	{
		new = ft_lstnew(BUFFER_SIZE);
		line_read = read(fd, new->storage, BUFFER_SIZE);
		if (line_read > 0)
			ft_lstadd_back(head, new);
		else
			ft_lstclear(&new);
		if (line_read != BUFFER_SIZE)
		{
			if (!*head)
			{
				*save_line = -1;
				return (NULL);
			}
			*(*head)->lread = -1;
			break;
		}
		*new_line = ft_lstcherch(&new);
	}
	*new_line = ft_lstcherch(head);
	*save_line = ft_lstsize(head, new_line);
	return (*head);
}

char*	get_next_line(int fd)
{
	static get_ln*	head;
	static int			save_line;
	static int			new_line;
	char*				line;

	if (fd < 0 || BUFFER_SIZE <= 0 || save_line == -1)
		return (NULL);
	head = ft_read(fd, &head, &new_line, &save_line);
	if (!head)
		return (NULL);
	line = ft_line(&head, &new_line, &save_line);
	if (head && save_line != -1)
		head = ft_data(&head, &save_line, &new_line);
	return (line);
}
