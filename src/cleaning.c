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

void	ft_free_images(t_game *game)
{
	if (!game || !game->mlx_connection)
		return ;

	if (game->images.floor)
		mlx_destroy_image(game->mlx_connection, game->images.floor);
	if (game->images.collectible)
		mlx_destroy_image(game->mlx_connection, game->images.collectible);
	if (game->images.exit)
		mlx_destroy_image(game->mlx_connection, game->images.exit);
	if (game->images.player_up_1)
		mlx_destroy_image(game->mlx_connection, game->images.player_up_1);
	if (game->images.player_up_2)
		mlx_destroy_image(game->mlx_connection, game->images.player_up_2);
	if (game->images.player_down_1)
		mlx_destroy_image(game->mlx_connection, game->images.player_down_1);
	if (game->images.player_down_2)
		mlx_destroy_image(game->mlx_connection, game->images.player_down_2);
	if (game->images.player_left_1)
		mlx_destroy_image(game->mlx_connection, game->images.player_left_1);
	if (game->images.player_left_2)
		mlx_destroy_image(game->mlx_connection, game->images.player_left_2);
	if (game->images.player_right_1)
		mlx_destroy_image(game->mlx_connection, game->images.player_right_1);
	if (game->images.player_right_2)
		mlx_destroy_image(game->mlx_connection, game->images.player_right_2);
}

int	handle_close(t_game *game)
{
	int	i;

	if (!game)
		exit (0);

	ft_free_images(game);
	if (game->mlx_wind && game->mlx_connection)
		mlx_destroy_window(game->mlx_connection, game->mlx_wind);

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	if (game->mlx_connection)
		free(game->mlx_connection);
		
	free(game);
	exit(0);
	return (0);
}