#include "get_next_line.h"

size_t	ft_check(get_line* head, char c)
{
	size_t	check;

	check = 0;
	while (head)
	{
		while (head->storage[check] != c)
			check++;
		if (head->storage[check] == c)
		{
			if(c == '\n')
				check++;
			return (ckeck);
		}
		head = head->next;
	}
	return (0);		
}

char*	ft_calloc(size_t size)
{
	char*	allocat;
	size_t	z;

	if (!size)
		return (NULL);
	allocat = (char*)malloc(sizeof(char) * (size + 1));
	if (!allocat)
		return (NULL);
	z = 0;
	while (size >= z)
		allocat[z++] = 0;
	return (allocat);
}

get_line*	ft_lstnew(size_t BUFFER_SIZE)
{
	get_line*	node;

	node = (get_line*)malloc(sizeof(get_line));
	if (!node)
		return (NULL);
	node->storage = ft_calloc(BUFFER_SIZE);
	node->line_read = 0;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(get_line **head, get_line *new)
{
	get_line*	node;
	if (!new || !head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	node = *head;
	while ((*node)-next)
		(*node) = (*node)->next;
	if (!(*node->next))
		(*node)-next = new;
}

get_line*	ft_chyata(get_line** head)
{
	get_line*	new;
	size_t		check;

	new = *head;
	check = ft_check(new, '\n');
}

get_line*	ft_save(int fd, get_line** head, ssize_t* line_read)
{
	get_line*	new;
	char*		buffer;
	size_t		check;

	check = 0;
	new = ft_lstnew(BUFFER_SIZE);
	while (!check)
	{
		*line_read = read(fd, new->storage, BUFFER_SIZE)
	}
}

char*	get_next_line(int fd)
{
	static get_line*	head;
	static size_t		check;
	size_t			new_line;
	char*			line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = ft_check(head, '\n');
	if (check && head.line_read != BUFFR_SIZE)
	{
		//ft_free(head);
		return (NULL);
	}
	if (!new_line)
	{
		head = ft_save(fd, &head, &(head.line_read));
		check = 1;
	}
	line = ft_strjoin(head, NULL, '\n');
	head = ft_chyata(&head);
	return (line);
}
