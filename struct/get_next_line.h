#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#define	BUFFER_SIZE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef	struct get_next_line
{
	static char*		storage;
	static ssize_t		line_read;
	struct get_next_line*	next;
}	get_line;
#endif
