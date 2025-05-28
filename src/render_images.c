/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:22 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/27 17:51:22 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_images(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.floor, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map.grid[y][x] == MAP_WALL)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.wall, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map.grid[y][x] == MAP_COLLECT)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.collectible, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map.grid[y][x] == MAP_EXIT)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.exit, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map.grid[y][x] == MAP_PLAYER)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.player, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	
}

void	ft_render_images(t_game *game)
{
	game->images.wall = mlx_xpm_file_to_image(game->mlx_connection, "assets/wall.xpm",
		&game->images.width, &game->images.height);
	game->images.floor = mlx_xpm_file_to_image(game->mlx_connection, "assets/floor.xpm",
		&game->images.width, &game->images.height);
	game->images.collectible =  mlx_xpm_file_to_image(game->mlx_connection, "assets/collectible.xpm",
		&game->images.width, &game->images.height);
	game->images.exit =  mlx_xpm_file_to_image(game->mlx_connection, "assets/exit.xpm",
		&game->images.width, &game->images.height);
	game->images.player =  mlx_xpm_file_to_image(game->mlx_connection, "assets/player.xpm",
		&game->images.width, &game->images.height);
}

void	ft_free_images(t_game *game)
{
	if (game && game->mlx_connection)
	{
		mlx_destroy_image(game->mlx_connection, game->images.wall);
		mlx_destroy_image(game->mlx_connection, game->images.floor);
		mlx_destroy_image(game->mlx_connection, game->images.collectible);
		mlx_destroy_image(game->mlx_connection, game->images.exit);
		mlx_destroy_image(game->mlx_connection, game->images.player);
	}
}

void	ft_update_grid(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
		game->images.floor, x * TILE_SIZE, y * TILE_SIZE);

	if (game->map.grid[y][x] == MAP_EXIT)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.exit, x * TILE_SIZE, y * TILE_SIZE);

	if (game->map.grid[y][x] == MAP_WALL)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.wall, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map.grid[y][x] == MAP_COLLECT)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.collectible, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map.grid[y][x] == MAP_PLAYER)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.player, x * TILE_SIZE, y * TILE_SIZE);
}

void	ft_display_moves(t_game *game)
{
	char	*moves;
	char	*tmp;

	tmp = ft_itoa(game->moves);
	moves = ft_strjoin("MOVES: ", tmp);
	mlx_string_put(game->mlx_connection, game->mlx_wind,
		10, 20, 0xFFFFFF, moves);
	free (tmp);
	free (moves);
}