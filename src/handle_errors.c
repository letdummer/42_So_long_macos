#include "so_long.h"

void	ft_error_message(char *message)
{
	ft_printf("Error %s%s\n", RED, message, END_COLOR);
	exit(1);
}