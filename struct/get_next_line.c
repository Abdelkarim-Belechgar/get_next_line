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

int	ft_lstcherch(gnl **head, char *str)
{
	// printf("++++++++++++ start ft_lstcherch ++++++++++++\n\n");
	int	z;


	z = 0;
	if (!*head && !str)
		return (-1);
	while (str && str[z] && *head)
	{
		if (str && str[z] == '\n')
		{
			(*head)->nline = (*head)->nline + z + 1;
			// printf("find new line\n");
			// printf("(*head)->nline = %d\n", (*head)->nline);
			// printf("(*head)->lread = %zd\n", (*head)->lread);
			return ((*head)->nline);
		}
		z++;
	}
	(*head)->nline += z;
	// printf("(*head)->nline = %d\n", (*head)->nline);
	// printf("(*head)->lread = %zd\n", (*head)->lread);
	if ((*head)->lread == -1)
	{
		// printf("****lread == -1***\nreturn last line = %d\n", (*head)->nline);
		return ((*head)->nline);
	}
	// printf("++++++++++++ end ft_lstcherch ++++++++++++\n\n");
	return (0);
}

gnl	*ft_data(gnl **head, char *str, int save_line, int zz, int *new_line)
{
	// printf("++++++++++++ start ft_data ++++++++++++\n\n");
	gnl	*new;
	int	z;

	z = 0;
	// printf("**save_line = %d\n", save_line);
	// printf("**new_line = %d\n", *new_line);
	if (!save_line)
	{
		ft_lstclear(head);
		head = NULL;
		*new_line = 0;
		return (NULL);
	}
	new = ft_lstnew(save_line);
	if ((*head)->lread == -1)
		new->lread = (*head)->lread;
	// printf("(*head)->lread = %zd\n", (*head)->lread);
	while (str && str[zz])
		new->storage[z++] = str[zz++];
	ft_lstclear(head);
	// printf("new->storage %s***\n", new->storage);
	// printf("******new->storage %s***\n", new->storage);
	*new_line = ft_lstcherch(&new, new->storage);
	// printf("**new_line = %d\n", *new_line);
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

	new = *head;
	line = ft_calloc((*head)->nline);
	y = 0;
	// printf("****save_line = %d***\n", *save_line);
	while (new && (*head)->nline > y)
	{
		z = 0;
		while (new->storage[z] && (*head)->nline > y)
			line[y++] = new->storage[z++];
		if (*new_line == y)
			break;
		new = new->next;
	}
	*save_line = ft_lstsize(head, &*new_line);
	// printf("****save_line = %d\n", *save_line);
	if (*save_line == -1)
		ft_lstclear(head);
	else
	{
		// printf("storage = %s\n", new->storage);
		*head = ft_data(head, new->storage, *save_line, z, &*new_line);
	}
	// printf("++++++++++++ end ft_line ++++++++++++\n\n");
	return (line);
}

gnl	*ft_read(int fd, gnl **head, int *line_size, int *line_save)
{
	// printf("************* start ft_read ***************\n\n");
	gnl		*new;
	static ssize_t	line_read;

	while (!*line_size && (!*head || (*head && !(*head)->lread)))
	{
		// printf("read\n");
		new = NULL;
		new = ft_lstnew(BUFFER_SIZE);
		line_read = read(fd, new->storage, BUFFER_SIZE);
		if (line_read > 0)
			ft_lstadd_back(head, new);
		else
		{
			ft_lstclear(&new);
			if (!*head)
			{
				*line_save = -1;
				return (NULL);
			}
		}
		if (line_read != BUFFER_SIZE)
			(*head)->lread = -1;
		// printf("*line_size = %d\n", *line_size);
		// printf("(*head)->lread = %zd\n", (*head)->lread);
		*line_size = ft_lstcherch(head, new->storage);

	}
	// if (*head)
	// 	printf("(*head)->lread = %zd\n", (*head)->lread);
	// printf("*line_size = %d\n", *line_size);
	// printf("************* end ft_read ***************\n\n");
	return (*head);
}

char	*get_next_line(int fd)
{
	static gnl		*save_data;
	static int		line_save;
	static int		line_size;
	char			*str_line;

	// printf("***line_save  *****= %d\n", line_save);
	// printf("***line_size  *****= %d\n", line_size);
	// printf("***save_data  *****= %p\n", save_data);
	if (fd < 0 || BUFFER_SIZE <= 0 || line_save == -1)
		return (NULL);
	save_data = ft_read(fd, &save_data, &line_size, &line_save);
	if (!save_data)
		return (NULL);
	// printf("save_data->storage = %s\n", save_data->storage);
	str_line = ft_line(&save_data, &line_size, &line_save);
	return (str_line);
}
