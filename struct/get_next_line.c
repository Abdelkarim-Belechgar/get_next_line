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

int	ft_lstcherch(gnl **head)
{
	// printf("++++++++++++ start ft_lstcherch ++++++++++++\n\n");
	gnl		*new;
	new = NULL;
	size_t	z;
	int		check;
	int		res;

	res = 0;
	check = 0;
	new = *head;
	// printf("address of **head %p\n", head);
	if (new)
	while (new)
	{
		z = 0;
		while (new->storage && new->storage[z] && new->storage[z] != '\n')
			z++;
		check += z;
		if (new->storage && new->storage[z] == '\n')
		{
			// printf("res + '\\n' = %d\n", check + 1);
			return (check + 1);
		}
		if (*head && !new->next && *(*head)->lread == -1)
			res = check;
		new = new->next;
	}
	printf("res = %d\n", res);
	// printf("++++++++++++ end ft_lstcherch ++++++++++++\n\n");
	return (res);
}

gnl	*ft_data(gnl **head, gnl *newz, int save_line, int zz)
{
	// printf("++++++++++++ start ft_data ++++++++++++\n\n");
	gnl	*new;
	int	z;

	z = 0;
	// printf("address of **head %p\n", head);
	// printf("**save_line = %d\n", save_line);
	new = ft_lstnew(save_line);
	while (newz && newz->storage[zz])
		new->storage[z++] = newz->storage[zz++];
	ft_lstclear(head);
	// printf("new->storage %s***\n", new->storage);
	// printf("++++++++++++ end ft_data ++++++++++++\n\n");
	return (new);
}

char	*ft_line(gnl **head, int *new_line, int *save_line)
{
	// printf("++++++++++++ start ft_line ++++++++++++\n\n");
	gnl		*new;
	char	*line;
	int		y;
	int		z;

	// printf("address of **head %p\n", head);
	new = *head;
	// printf("buffer_size = %d\n", BUFFER_SIZE);
	// printf("*new_line = %d\n", *new_line);
	line = ft_calloc(*new_line);
	y = 0;
	while (new && *new_line > y)
	{
		z = 0;
		while (new->storage[z] && *new_line > y)
			line[y++] = new->storage[z++];
		if (*new_line <= y)
			break;
		new = new->next;
	}
	// printf("line = %s***\n", line);
	*save_line = ft_lstsize(head, &*new_line);
	// printf("*save_line size = %d\n", *save_line);
	if (*save_line == -1)
	{
		// printf("head is clear\n");
		ft_lstclear(head);
	}
	else
	{
		// printf("ghadi ndkhlo ldata\n");
		*head = ft_data(head, new, *save_line, z);
		// printf("(*head)->storage %s***\n", (*head)->storage);
	}
	*new_line = ft_lstcherch(head);
	// printf("++++++++++++ end ft_line ++++++++++++\n\n");
	return (line);
}

gnl	*ft_read(int fd, gnl **head, int *new_line, int *save_line)
{
	// printf("************* start ft_read ***************\n\n");
	gnl		*new;
	ssize_t	line_read;

	// printf("address of **head %p\n", head);
	// printf("/////create linked list /////\n");
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
			// printf("line_read != BUFFER_SIZE\n");
			if (!*head)
			{
				*save_line = -1;
				return (NULL);
			}
			*(*head)->lread = -1;
			break ;
		}
		*new_line = ft_lstcherch(&new);
	}
	*new_line = ft_lstcherch(head);
	// printf("head->storage = %s\n", (*head)->storage);
	// printf("///// linked list /////\n");
	// printf("************* end ft_read ***************\n\n");
	return (*head);
}

char	*get_next_line(int fd)
{
	// printf("************* start get_next_line ***************\n\n");
	static gnl		*head;
	static int		save_line;
	static int		size_line;
	char			*str_line;

	// printf("save_line = %d\n", save_line);
	// printf("size_line = %d\n", size_line);
	if (fd < 0 || BUFFER_SIZE <= 0 || save_line == -1)
		return (NULL);
	head = ft_read(fd, &head, &size_line, &save_line);
	if (!head)
		return (NULL);
	str_line = ft_line(&head, &size_line, &save_line);
	// printf("************* end get_next_line ***************\n\n");
	return (str_line);
}
