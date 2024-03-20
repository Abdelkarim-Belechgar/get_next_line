/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:33:41 by abelechg          #+#    #+#             */
/*   Updated: 2024/02/22 06:33:43 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
typedef	struct t_list
{
	struct t_list	*preavis;
	char			*storage;
	ssize_t			lread;
	int				fd;
	int				nline;
	struct t_list	*next;
}	gnl;

gnl		*create_new_node(size_t size);
void	add_back_node(gnl **head, gnl *new);
void	clear_linked_list(gnl **head);
int		update_node_size(gnl **head, int index);
int		search_for_nline(gnl **head);
gnl		*update_node_save(gnl **head, int index, int *new_line, int *save_line);
char	*store_new_line(gnl **head, int *new_line, int *save_line);
gnl		*read_data(int fd, gnl **head, int *new_line, int *line_save);
char	*get_next_line(int fd);
#endif