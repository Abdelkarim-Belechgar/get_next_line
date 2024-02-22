/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:33:55 by abelechg          #+#    #+#             */
/*   Updated: 2024/02/22 06:34:00 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char*	ft_calloc(size_t size)
{
	char*	allocat;
	size_t	z;

	if (!size)
		return (NULL);
	allocat = (char*)malloc(sizeof(char) * (size + 1));
	if (!allocat)
		return (NULL);
	z = 0;
	while (size >= z)
		allocat[z++] = 0;
	return (allocat);
}

get_line*	ft_lstnew(size_t size)
{
	get_line*	node;

	node = (get_line*)malloc(sizeof(get_line));
	if (!node)
		return (NULL);
	node->storage = ft_calloc(size);
	node->lread = malloc(sizeof(ssize_t));
	*node->lread = 0;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(get_line **head, get_line *new)
{
	get_line*	node;

    if (!new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node->next)
		node = node->next;
	if (!node->next)
		node->next = new;
}

void	ft_lstclear(get_line** head)
{
	get_line*	new;

	if (!*head || !head)
		return ;
	while (*head)
	{
		new = (*head)->next;
		free((*head)->storage);
		(*head)->storage = NULL;
		free((*head)->lread);
		(*head)->storage = NULL;
		free(*head);
		*head = new;
	}
}

int	ft_lstsize(get_line **lst, int* nline)
{
    get_line*   node;
    int      size;
    int      start;
	int  	z;
	int	    y;

	z = 0;
	size = 0;
    start = *nline;
    node = *lst;
	while (start && node)
	{
		y = 0;
		while (node && node->storage[y])
			y++;
		z += y;
		node = node->next;
	}
    size = z - start;
    if (!size && *lst && *(*lst)->lread == -1)
        return (-1);
	return (size);
}
