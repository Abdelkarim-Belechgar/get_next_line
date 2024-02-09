#include "get_next_line.h"

size_t	ft_check(get_line* head, char c)
{
	size_t	check;

	check = 0;
	while (head)
	{
		while ((head->storage)[check] != c)
			check++;
		if ((head->storage)[check] == c)
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
	node->line_read = BUFFER_SIZE;
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
	while (node-next)
		node = node->next;
	if (!node->next))
		node-next = new;
}

char*	ft_line(get_line* head, char c)
{
	char*	line;
	size_t	size;
	size_t	z;

	z = 0;
	size = ft_check(head, c);
	line = ft_calloc(size);
	while (head)
	{
		while (size > z)
		{
			line->storage[z] = head->storage[z];
			z++;
		}
		head = head->next;
	}
	return (line)
}

get_line*	ft_data(get_line** head)
{
	get_line*	new;
	size_t		check;

	new = *head;
	check = ft_check(new, '\n');
	check = ft_check(new + check, '\0');
	if (!check)
		return (NULL);
	new = ft_lstnew(check);
	
	new = ft_line(, '\0');
}

void	ft_free(get_line** head)
{
	get_line*	new;

	while (*head)
	{
		new = (*head)->next;
		free((*head)->storage);
		(*head)->storage = NULL;
		free(*head);
		*head = new;
	}
}

get_line*	ft_read(int fd, get_line** head, ssize_t* line_read)
{
	get_line*	new;
	size_t		check;

	check = ft_check(*head, '\n');
	if (check > 0)
	{
		(*head).line_read = BUFFER_SIZE;
		return (*head);
	}
	while (!check)
	{
		new = ft_lstnew(BUFFER_SIZE);
		*line_read = read(fd, new->storage, BUFFER_SIZE)
		printf("read = %s---\n", new_storage);
		head = ft_lstadd_back(head, new);
		check = ft_check(*head, '\n');
		ft_free(&new);
	}
	return (*head);
}

char*	get_next_line(int fd)
{
	static get_line*	head;
	char*			line;

	if (fd < 0 || (BUFFER_SIZE <= 0 && head.line_read != BUFFER_SIZE))
		return (NULL);
	head = ft_read(fd, &head, &head.line_read);
	line = ft_line(head, '\n');
	head = ft_data(&head);
	return (line);
}
