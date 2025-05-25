#include "so_long.h"

void	ft_error_message(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(1);
}

void    gnl_clear(int fd)
{
    char    *temp;

    if (fd < 0)
        return;
    temp = get_next_line(fd);
    while (temp)
    {
        free(temp);
        temp = get_next_line(fd);
    }
}