/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 05:06:05 by abelechg          #+#    #+#             */
/*   Updated: 2024/03/28 05:06:10 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	char	*str;
	int		fd;

	fd = open("test", O_RDONLY);
	printf("fd = %d\n", fd);
	printf("*");
	while (1)
	{
		str = get_next_line(fd);
		printf("%s*", str);
		if (!str)
			break ;
		free(str);
	}
}
