/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:54:30 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/21 05:54:32 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct t_list
{
	char			*storage;
	ssize_t			lread;
	int				nline;
	struct t_list	*next;
}	t_line;

void	clear_linked_list(t_line **head);
t_line	*create_new_node(size_t size);
void	add_back_node(t_line **head, t_line *new);
int		save_node_size(t_line *node, int index);
int		search_for_nline(t_line **head);
t_line	*update_node(t_line **head, int index, int save_line);
char	*store_new_line(t_line **head, ssize_t new_line, int save_line);
t_line	*read_data(int fd, t_line **head, ssize_t *new_line);
char	*get_next_line(int fd);

#endif
