#include "../includes/so_long.h"
#include "../mlx/minilibx-linux/mlx.h"

#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h"

void	ft_validate_map(char *file)
{
	char	*extension;

	if (file == NULL)
		ft_error_message("Invalid file!");
	extension = ft_strrchr(file, '.');
	if (extension == NULL || ft_strcmp(extension, ".ber") != 0)
		ft_error_message("Invalid file. Must be '.ber");
}