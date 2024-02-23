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
#define	BUFFER_SIZE 5
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
typedef	struct get_next_line
{
	char*					storage;
	ssize_t*				lread;
	struct get_next_line*	next;
}	get_ln;

char*		ft_calloc(size_t size);
get_ln*		ft_lstnew(size_t size);
void		ft_lstadd_back(get_ln **head, get_ln *new);
void		ft_lstclear(get_ln** head);
get_ln*		ft_read(int fd, get_ln** head, int* new_line, int* save_line);
get_ln*		ft_data(get_ln** head, int* save_line, int* new_line);
char*		ft_line(get_ln** head, int* new_line, int* save_line);
int			ft_lstcherch(get_ln** head);
int			ft_lstsize(get_ln **lst, int* new_line);
char*		get_next_line(int fd);

#endif