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
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

char	*get_next_line(int fd);
void	clear_string(char **str);
ssize_t	search_for_nline(char *str, ssize_t *size_flag);
char	*read_data(int fd, char **storage, ssize_t *size_flag, ssize_t *size_line);
char	*join_string(char **stoarge, char *buffer, ssize_t *size_flag, ssize_t *size_line);

#endif
