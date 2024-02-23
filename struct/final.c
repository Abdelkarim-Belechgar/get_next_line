/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelechg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:34:33 by abelechg          #+#    #+#             */
/*   Updated: 2024/02/23 00:34:40 by abelechg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

gnl	*ft_read(int fd, gnl **head, int *new_line, int *save_line)
{
	gnl		*new;
	ssize_t	line_read;

	while (!*head || !*new_line)
	{
		new = ft_lstnew(BUFFER_SIZE);
		line_read = read(fd, new->storage, BUFFER_SIZE);
		if (line_read > 0)
			ft_lstadd_back(head, new);
		else
			ft_lstclear(&new);
		if (line_read != BUFFER_SIZE)
		{
			if (!*head)
			{
				*save_line = -1;
				return (NULL);
			}
			*(*head)->lread = -1;
			break ;
		}
		*new_line = ft_lstcherch(&new);
	}
	*new_line = ft_lstcherch(head);
	return (*head);
}
