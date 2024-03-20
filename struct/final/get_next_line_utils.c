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

void	clear_linked_list(gnl **head) // 17
{
	gnl		*new;

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

gnl	*create_new_node(size_t size) // 16
{
	gnl		*node;

	if (!size)
		return (NULL);
	node = (gnl *)malloc(sizeof(gnl));
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

void	add_back_node(gnl **head, gnl *new) // 12
{
	gnl		*node;

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

int	update_node_size(gnl **head, int index) // 11
{
	int		size;
	gnl		*node;

	if (!head || !*head)
		return (0);
	node = *head;
	if (node->next)
		node = node->next;
	size = 0;
	while (node->storage && node->storage[index + size])
		size++;
	return (size);
}

int	search_for_nline(gnl **head) // 22
{
	gnl	*new;
	int	z;

	z = 0;
	if (head && *head)
	{
		new = *head;
		while (new->next)
			new = new->next;
		while (new->storage && new->storage[z])
		{
			if (new->storage[z] == '\n')
			{
				(*head)->nline = (*head)->nline + z + 1;
				return ((*head)->nline);
			}
			z++;
		}
		(*head)->nline += z;
		if ((*head)->lread == -1)
			return ((*head)->nline);
	}
	return (0);
}
