/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:22 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/30 11:27:56 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_images(t_game *game)
{
	int		x;
	int		y;
	char	*wall_path;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
				game->images.floor, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == MAP_WALL)
			{
				wall_path = ft_walls_tiles(game, x, y);
				game->images.wall = mlx_xpm_file_to_image(game->mlx_connection,
					wall_path, &game->images.width, &game->images.height);
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.wall, x * TILE_SIZE, y * TILE_SIZE);
				mlx_destroy_image(game->mlx_connection, game->images.wall);
			}
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
	game->images.floor = mlx_xpm_file_to_image(game->mlx_connection, "assets/walls/tile_1_1.xpm",
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
		if (game->images.wall)
		    mlx_destroy_image(game->mlx_connection, game->images.wall);
		if (game->images.floor)
		    mlx_destroy_image(game->mlx_connection, game->images.floor);
		if (game->images.collectible)
		    mlx_destroy_image(game->mlx_connection, game->images.collectible);
		if (game->images.exit)
		    mlx_destroy_image(game->mlx_connection, game->images.exit);
		if (game->images.player)
		    mlx_destroy_image(game->mlx_connection, game->images.player);
	}
}

void	ft_update_grid(t_game *game, int x, int y)
{   
	char	*wall_path;

	mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
		game->images.floor, x * TILE_SIZE, y * TILE_SIZE);
    if (game->map.grid[y][x] == MAP_WALL)
    {
		wall_path = ft_walls_tiles(game, x, y);
		game->images.wall = mlx_xpm_file_to_image(game->mlx_connection,
			wall_path, &game->images.width, &game->images.height);
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.wall, x * TILE_SIZE, y * TILE_SIZE);
		mlx_destroy_image(game->mlx_connection, game->images.wall);
    }
	if (game->map.grid[y][x] == MAP_COLLECT)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.collectible, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map.grid[y][x] == MAP_EXIT)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.exit, x * TILE_SIZE, y * TILE_SIZE);
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

char	*ft_walls_tiles(t_game *game, int x, int y)
{
	if (x == 0 && y == 0)
		return (WALL_TOP_LEFT);
	if (x == game->map.width - 1 && y == 0)
		return (WALL_TOP_RIGHT);
	if (x == 0 && y == game->map.height - 1)
		return (WALL_BOTTOM_LEFT);
	if (x == game->map.width - 1 && y == game->map.height - 1)
		return (WALL_BOTTOM_RIGHT);

	if (y == 0)
		return (WALL_TOP);
	if (y == game->map.height - 1)
		return (WALL_BOTTOM);
	if (x == 0)
		return (WALL_LEFT);
	if (x == game->map.width - 1)
		return (WALL_RIGHT);
	return (WALL);
}