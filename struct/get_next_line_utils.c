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

char	*ft_calloc(size_t size)
{
	printf("++++++++++++ start ft_calloc ++++++++++++\n\n");
	char	*allocat;
	size_t	z;

	printf("size = %zu\n", size);
	if (!size)
		return (NULL);
	allocat = (char *)malloc(sizeof(char) * (size + 1));
	if (!allocat)
		return (NULL);
	z = 0;
	while (size >= z)
	{
		printf("size[%zu] = %d\n", z, BUFFER_SIZE);
		allocat[z++] = 0;
	}
	printf("++++++++++++ end ft_calloc ++++++++++++\n\n");

	return (allocat);
}

gnl	*ft_lstnew(size_t size)
{
	printf("++++++++++++ start ft_lstnew ++++++++++++\n\n");
	gnl		*node;

	node = NULL;
	printf("size = %zu\n", size);
	printf("address stack of &node = %p\n", &node);
	printf("address heap of node = %p\n", node);
	printf("alocate struct\n");
	node = (gnl *)malloc(sizeof(gnl));
	if (!node)
		return (NULL);
	// printf("size of struct = %zu\n", sizeof(gnl));
	// printf("address heap of &node = %p\n", &node);
	// printf("address heap of node = %p\n", node);
	// printf("address heap ponter of &node->storage = %p\n", &node->storage);
	// printf("address heap storage of node->storage = %p\n", node->storage);
	node->storage = ft_calloc(size);
	// printf("address heap ponter of &node->storage = %p\n", &node->storage);
	// printf("address heap storage of node->storage = %p\n", node->storage);
	// printf("size of node->storage = %zu\n", sizeof(node->storage));
	// printf("address heap of &node->lread = %p\n", &node->lread);
	// printf("address heap of node->lread = %p\n", node->lread);
	node->lread = malloc(sizeof(ssize_t));
	*node->lread = 0;
	// printf("address heap of &node->lread = %p\n", &node->lread);
	// printf("address heap of node->lread = %p\n", node->lread);
	// printf("size of node->lread = %zu\n", sizeof(node->lread));
	// printf("address heap of &node->next = %p\n", &node->next);
	// printf("address heap of node->next = %p\n", node->next);
	node->next = 0;
	// printf("address heap of &node->next = %p\n", &node->next);
	// printf("address heap of node->next = %p\n", node->next);
	// printf("++++++++++++ end ft_lstnew ++++++++++++\n\n");
	return (node);
}

void	ft_lstadd_back(gnl **head, gnl *new)
{
	printf("++++++++++++ start ft_lstadd_back ++++++++++++\n\n");
	gnl		*node;

	printf("address stack of &new = %p\n", &new);
	printf("address heap of new = %p\n", new);
	printf("address stack of &head = %p\n", &head);
	printf("address stack get_next_line  head = %p\n", head);
	printf("address heap get_next_line  *head = %p\n", *head);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		printf("address stack of &head = %p\n", &head);
		printf("address stack get_next_line  head = %p\n", head);
		printf("address heap get_next_line  *head = %p\n", *head);
		printf("++++++++++++ end ft_lstadd_back ++++++++++++\n\n");
		return ;
	}
	node = *head;
	while (node->next)
		node = node->next;
	if (!node->next)
		node->next = new;
	printf("address stack of &head = %p\n", &head);
	printf("address stack get_next_line  head = %p\n", head);
	printf("address heap get_next_line  *head = %p\n", *head);
	printf("++++++++++++ end ft_lstadd_back ++++++++++++\n\n");
}

void	ft_lstclear(gnl **head)
{
	printf("++++++++++++ start ft_lstclear ++++++++++++\n\n");
	gnl		*new;


	if (!*head || !head)
		return ;
	while (head && *head)
	{
		printf("address of **head = %p\n", head);
		printf("address of *head = %p\n", *head);
		new = (*head)->next;
		free((*head)->storage);
		(*head)->storage = NULL;
		free((*head)->lread);
		(*head)->storage = NULL;
		free(*head);
		*head = new;
	}
	printf("++++++++++++ end ft_lstclear ++++++++++++\n\n");
}

int	ft_lstsize(gnl **lst, int	*nline)
{
	gnl		*node;
	int		size;
	int		start;
	int		z;
	int		y;

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
