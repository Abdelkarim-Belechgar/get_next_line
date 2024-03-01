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

gnl	*create_new_node(size_t size) // 20
{
	gnl		*node;
	size_t	z;

	if (!size)
		return (NULL);
	z = 0;
	node = (gnl *)malloc(sizeof(gnl));
	if (!node)
		return (NULL);
	node->storage = (char *)malloc(sizeof(char) * (size + 1));
	if (!node->storage)
	{
		clear_linked_list(&node);
		return (NULL);
	}
	while (size >= z)
		node->storage[z++] = 0;
	node->lread = 0;
	node->nline = 0;
	node->next = NULL;
	return (node);
}

void	add_back_node(gnl **head, gnl *new) // 13
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
	if (!node->next)
		node->next = new;
}

void	clear_linked_list(gnl **head) // 
{
	gnl		*new;

	if (!*head || !head)
		return ;
	while (head && *head)
	{
		new = (*head)->next;
		free((*head)->storage);
		(*head)->storage = NULL;
		(*head)->lread = 0;
		(*head)->nline = 0;
		free(*head);
		*head = new;
	}
	*head = NULL;
}

int	update_node_size(gnl **head, int index) // 
{
	int		size;
	gnl		*node;

	node = *head;
	if (!*head)
		return (0);
	if (node->next)
		node = node->next;
	size = 0;
	while (node->storage && node->storage[index + size])
		size++;
	return (size);
}
