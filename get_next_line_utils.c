/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:54:17 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/21 05:54:20 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_linked_list(t_line **head)
{
	t_line	*new;

	if (!head || !*head)
		return ;
	while (head && *head)
	{
		new = (*head)->next;
		if ((*head)->storage)
		{
			free((*head)->storage);
			(*head)->storage = NULL;
		}
		(*head)->lread = 0;
		(*head)->nline = 0;
		free(*head);
		*head = new;
	}
	*head = NULL;
}

t_line	*create_new_node(size_t size)
{
	t_line	*node;

	if (!size)
		return (NULL);
	node = (t_line *)malloc(sizeof(t_line));
	if (!node)
		return (NULL);
	node->storage = (char *)malloc(sizeof(char) * (size + 1));
	if (!node->storage)
	{
		clear_linked_list(&node);
		return (NULL);
	}
	node->lread = 0;
	node->nline = 0;
	node->next = NULL;
	return (node);
}

void	add_back_node(t_line **head, t_line *new)
{
	t_line	*node;

	if (!new)
		return ;
	if (!head || !*head)
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node->next)
		node = node->next;
	node->next = new;
}

int	save_node_size(t_line *node, int index)
{
	int		size;

	if (!node)
		return (0);
	if (node->next)
		node = node->next;
	size = 0;
	while (node->storage && node->storage[index + size])
		size++;
	return (size);
}

int	search_for_nline(t_line **head)
{
	t_line	*new;
	int		z;

	z = 0;
	if (!head || !*head)
		return (0);
	new = *head;
	while (new->next)
		new = new->next;
	while ((*head)->lread && new->storage && new->storage[z])
	{
		if (new->storage[z] == '\n')
		{
			(*head)->nline = (*head)->nline + z + 1;
			return ((*head)->nline);
		}
		z++;
	}
	(*head)->nline += z;
	if ((*head)->lread != BUFFER_SIZE)
		return ((*head)->nline);
	return (0);
}
