/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 05:06:05 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/28 05:06:10 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_string(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

ssize_t search_for_nline(char *str, ssize_t *size_flag)
{
	ssize_t	size;

	if (!str)
		return (0);
	size = 0;
	while (str && str[size])
	{
		if (str[size] == '\n')
			return (size + 1);
		size++;
	}
	*size_flag += size;
	return (0);
}
