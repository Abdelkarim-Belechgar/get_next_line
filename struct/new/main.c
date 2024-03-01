#include "get_next_line.h"

// void doublecheck(char** str)
// {
// 	// printf("address of stack check &***str = %p\n", &***str);
// 	printf("address of stack check &**str = %p\n", &**str);
// 	// printf("address of heap in main **str = %p\n", **str);
// 	printf("address of stack check &*str = %p\n", &*str);
// 	printf("address of heap in main *str = %p\n", *str);
// 	printf("address of stack check &str = %p\n", &str);
// 	printf("address of stack in main str = %p\n", str);
// }

// void check(char** str)
// {
// 	printf("start check\n\n");
// 		printf("address of stack check &**str = %p\n", &**str);
// 	printf("address of stack check &*str = %p\n", &*str);
// 	printf("address of heap in main *str = %p\n", *str);
// 	printf("address of stack check &str = %p\n", &str);
// 	printf("address of stack in main str = %p\n", str);
// 	// printf("address of heap in main *str = %p\n", **str);
// 	printf("end check\n\n");
// 	doublecheck(str);
// }
	// char*	str;

	// str = NULL;
	// printf("address of stack &str = %p\n", &str);
	// printf("address of value str = %p\n", str);
	// str = malloc(sizeof(char) * 6);
	// str = "hello";
	// printf("address of stack &str = %p\n", &str);
	// printf("address of  heap value str = %p\n", str);

	// check(&str);

int main(void)
{
	char*	new;
	int		fd;
	size_t	z;
	fd = open("test.txt", O_RDONLY);
	z = 0;
	while(1)
	{
		new = get_next_line(fd);
		printf("%s",new);
		if(new == NULL)
			break;
		free(new);
	}
	// system("leaks a.out");
    return (0);
}