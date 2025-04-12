#include "so_long.h"

void	ft_error_message(char *message)
{
	ft_printf("Error\n%s\n",  message);
	exit(1);
}

void ft_cleanup(t_game *game)
{
	int	i;

	if (!game)
		return;
	if (game->mlx_wind && game->mlx_connection)
		mlx_destroy_window(game->mlx_connection, game->mlx_wind);
	if (game->mlx_connection)
	{
		ft_free_images(game);
		free(game->mlx_connection);
	}
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	free(game);
}