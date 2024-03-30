/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 05:06:16 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/28 05:07:47 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
void	clear_string(char **data);
size_t	search_for_nline(char *buffer, size_t *flag);
char	*read_data(int fd, char **data, size_t *flag, ssize_t size);
void	join_string(char **data, char *buffer, size_t flag, ssize_t size);
char	*sorte_new_line(char *data, size_t flag);
void	update_data(char **data, size_t flag);
size_t	update_size(char *data);

#endif
