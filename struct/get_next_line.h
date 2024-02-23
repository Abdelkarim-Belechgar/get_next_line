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
#define	BUFFER_SIZE 10
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
typedef	struct t_list
{
	char*					storage;
	ssize_t*				lread;
	struct t_list*	next;
}	gnl;

char	*ft_calloc(size_t size);
gnl		*ft_lstnew(size_t size);
void	ft_lstadd_back(gnl **head, gnl *new);
void	ft_lstclear(gnl **head);
gnl		*ft_read(int fd, gnl **head, int *new_line, int *save_line);
gnl		*ft_data(gnl **head, gnl *new, int save_line, int z);
char	*ft_line(gnl **head, int *new_line, int *save_line);
int		ft_lstcherch(gnl **head);
int		ft_lstsize(gnl **lst, int *new_line);
char	*get_next_line(int fd);

#endif
