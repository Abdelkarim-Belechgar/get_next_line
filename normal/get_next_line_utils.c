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

void	clear_string(char **data)
{
	if (data && *data && **data)
	{
		free(*data);
		*data = NULL;
	}
}

size_t	update_size(char *data)
{
	size_t	z;

	z = 0;
	while (data && data[z])
		z++;
	return (z);
}

size_t	search_for_nline(char *buffer, size_t *flag)
{
	size_t	size;

	size = 0;
	while (buffer && buffer[size])
	{
		if (buffer[size] == '\n')
		{
			*flag = *flag + size + 1;
			return (*flag);
		}
		size++;
	}
	*flag += size;
	return (0);
}

void	join_string(char **data, char *buffer, size_t flag, ssize_t size)
{
	char	*save;
	size_t	z;

	save = (char *)malloc(sizeof(char) * (flag + size + 1));
	if (!save)
	{
		clear_string(data);
		return ;
	}
	z = 0;
	if (data && *data)
	{
		while ((*data)[z])
		{
			save[z] = (*data)[z];
			z++;
		}
	}
	while (buffer && *buffer)
		save[z++] = *buffer++;
	save[z] = '\0';
	clear_string(data);
	*data = save;
}
