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

int	search_for_nline(gnl **head) // 21
{
	// printf("********* start search_for_nline ********\n\n");
	gnl	*new;
	int	z;

	z = 0;
	if (*head)
	{
		new = *head;
		while (new->next)
			new = new->next;
		while (new->storage && new->storage[z])
		{
			if (new->storage[z] == '\n')
			{
				(*head)->nline = (*head)->nline + z + 1;
				// printf("------------ end have new line search_for_nline = %d ------------\n\n", (*head)->nline);
				return ((*head)->nline);
			}
			z++;
		}
		(*head)->nline += z;
		if ((*head)->lread == -1)
		{
			// printf("------------ end last line (*head)->lread == -1 search_for_nline = %d ------------\n\n", (*head)->nline);
			return ((*head)->nline);
		}
	}
	// printf("------------ end 0 search_for_nline ------------\n\n");
	return (0);
}

gnl	*update_node_save(gnl **head, int index, int *new_line, int *save_line)
{
	// printf("********* start cupdate_node_save ********\n\n");
	gnl	*new;
	gnl	*node;
	int	z;

	z = 0;
	new = NULL;
	node = *head;
	// printf("1 + save_line = %d\n", *save_line);
	while (node->next)
		node = node->next;
	if (*save_line > 0)
	{
		// printf("save node = %d\n", *save_line);
		// printf("index = %d\n", index);
		// printf("(*head)->storage  = %s\n", (*head)->storage);
		new = create_new_node(*save_line);
		new->lread = (*head)->lread;
		while (node->storage && node->storage[index + z])
		{
			new->storage[z] = node->storage[index + z];
			z++;
		}
		new->storage[z] = 0;
		*save_line = 0;
		// printf("new node->storage = %s\n", new->storage);
	}
	// if (!*save_line && *head && (*head)->lread == -1)
	// 	*save_line = -1;
	clear_linked_list(head);
	// if (!*head)
	// 	printf(" 2 + save_line = %d\n", *save_line);
	*new_line = search_for_nline(&new);
	// printf("*new_line = %d\n", *new_line);
	// printf("head addreass = %p\n", head);
	// printf("&*head addreass = %p\n", &*head);
	// printf("*head addreass = %p\n", *head);
	// printf("&**head addreass = %p\n", &**head);
	// printf("de_bug\n");
	// if (new)
	// 	printf("size of (*head)->lread = %zd\n", new->lread);
	// printf("----------- end cupdate_node_save -----------\n\n");
	return (new);
}

char	*store_new_line(gnl **head, int *new_line, int *save_line)
{
	// printf("********* start storge_new_line ********\n\n");
	gnl		*new;
	char	*line;
	int		index;
	int		y;

	new = *head;
	// printf("size of line = %d\n", *save_line + *new_line + 1);
	line = (char *)malloc(sizeof(char) * (*save_line + *new_line + 1));
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
	// printf("index = %d\n", index);
	// printf("line = %s***\n", line);
	// printf("1 (*head)->lread = %zd\n", (*head)->lread);
	// printf("1 (*head)->storage = %s\n", (*head)->storage);
	// if (*head && new)
	// 	printf("de_bug!\n");
	*save_line = update_node_size(&new, index);
	// printf("1 size of node->storage = %d\n", *save_line);
	// printf("1 size of new_line = %d\n", *new_line);
	// printf("1 (*head)->nline = %d\n", (*head)->nline);
	if (!*save_line && *head && (*head)->lread == -1)
		*save_line = -1;
	*head = update_node_save(head, index, &*new_line, &*save_line);
	// if (*head)
	// {
	// 	printf("2 size of node->storage = %d\n", *save_line);
	// 	printf("2 size of new_line = %d\n", *new_line);
	// 	printf("2 (*head)->lread = %zd\n", (*head)->lread);
	// 	printf("2 (*head)->nline = %d\n", (*head)->nline);
	// }
	// printf("----------- end storge_new_line -----------\n\n");
	return (line);
}

gnl	*read_data(int fd, gnl **head, int *new_line, int *save_line) // 23
{
	// printf("********* start read_data ********\n\n");
	gnl		*new;
	ssize_t	line_read;

	// printf("1 *new_line = %d\n", *new_line);
	// printf("2 *save_line = %d\n", *save_line);
	// gnl	*test;
	// test = *head;
	// if (test)
	// {
	// 	printf("find head\n");
	// 	printf("1 save_data->lread = %zd\n", test->lread);
	// 	printf("1 save_data->nline = %d\n", test->nline);
	// }
	// if (test)
	// {
	// 	printf("1 save_data->storage = %s\n", test->storage);
	// 	test = test->next;
	// }
	while (!*new_line)
	{
		new = NULL;
		new = create_new_node(BUFFER_SIZE);
		line_read = read(fd, new->storage, BUFFER_SIZE);
		// printf("new/->storage = %s\n", new->storage);
		if (line_read > 0)
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
		if (line_read != BUFFER_SIZE)
			(*head)->lread = -1;
		*new_line = search_for_nline(head);
	}
	// printf("2 *new_line = %d\n", *new_line);
	// printf("2 *save_line = %d\n", *save_line);
	// test = *head;
	// if (test)
	// {
	// 	printf("2 save_data->lread = %zd\n", test->lread);
	// 	printf("2 save_data->nline = %d\n", test->nline);
	// }
	// while (test)
	// {
	// 	printf("2 save_data->storage = %s", test->storage);
	// 	test = test->next;
	// }
	// printf("------------ start read_data ------------\n\n");
	return (*head);
}

char	*get_next_line(int fd)
{
	// printf("********* start get_next_line ********\n\n");
	static gnl		*save_data;
	static int		new_line;
	static int		save_line;
	char			*str_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || save_line == -1)
		return (NULL);
	// printf("&save_data addreass = %p\n", &save_data);
	// printf("save_data addreass = %p\n", save_data);
	// if (save_data)
	// {
	// 	printf("1 save_data->storage = %s\n", save_data->storage);
	// 	printf("1 save_data->lread = %zd\n", save_data->lread);
	// 	printf("1 save_data->nline = %d\n", save_data->nline);
	// }
	// printf("new_line = %d\n", new_line);
	// printf("save_line = %d\n", save_line);
	save_data = read_data(fd, &save_data, &new_line, &save_line);
	if (!save_data)
		return (NULL);
	// if (save_data && save_data->storage)
	// printf("save_data->storage = %s\n", save_data->storage);
	// printf("&save_data addreass = %p\n", &save_data);
	// printf("save_data addreass = %p\n", save_data);
	str_line = store_new_line(&save_data, &new_line, &save_line);
	// if (save_data)
	// {
	// 	// printf("2 save_data->storage = %s\n", save_data->storage);
	// 	// printf("2 save_data->lread = %zd\n", save_data->lread);
	// 	// printf("2 save_data->nline = %d\n", save_data->nline);
	// }
	// printf("&save_data addreass = %p\n", &save_data);
	// printf("save_data addreass = %p\n", save_data);
	// printf("new_line = %d\n", new_line);
	// printf("save_line = %d\n", save_line);
	// printf("--------- end get_next_line -----------\n\n");
	return (str_line);
}
