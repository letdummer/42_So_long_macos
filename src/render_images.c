/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:22 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/30 19:09:07 by ldummer-         ###   ########.fr       */
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
				void *temp_wall = mlx_xpm_file_to_image(game->mlx_connection,
					wall_path, &game->images.width, &game->images.height);
				if (temp_wall)
				{
					mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
						temp_wall, x * TILE_SIZE, y * TILE_SIZE);
					mlx_destroy_image(game->mlx_connection, temp_wall);
				}
			}
			if (game->map.grid[y][x] == MAP_COLLECT)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.collectible, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map.grid[y][x] == MAP_EXIT)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.exit, x * TILE_SIZE, y * TILE_SIZE);
			if (game->map.grid[y][x] == MAP_PLAYER)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					ft_player_images(game), x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	ft_render_images(t_game *game)
{
	game->images.floor = mlx_xpm_file_to_image(game->mlx_connection, "assets/walls/tile_1_1.xpm",
		&game->images.width, &game->images.height);
	game->images.wall = NULL;
	game->images.collectible =  mlx_xpm_file_to_image(game->mlx_connection, "assets/collectible.xpm",
		&game->images.width, &game->images.height);
	game->images.exit =  mlx_xpm_file_to_image(game->mlx_connection, "assets/exit.xpm",
		&game->images.width, &game->images.height);

	game->images.player_up_1 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_UP_1,
		&game->images.width, &game->images.height);
	if (!game->images.player_up_1)
        ft_error_message("Failed to load player up 1 image");

	game->images.player_up_2 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_UP_2,
		&game->images.width, &game->images.height);
	if (!game->images.player_up_2)
			ft_error_message("Failed to load player up 2 image");

	game->images.player_down_1 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_DOWN_1,
		&game->images.width, &game->images.height);
	if (!game->images.player_down_1)
			ft_error_message("Failed to load player down 1 image");
		
	game->images.player_down_2 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_DOWN_2,
		&game->images.width, &game->images.height);
	if (!game->images.player_down_2)
			ft_error_message("Failed to load player down 2 image");

		
	game->images.player_left_1 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_LEFT_1,
		&game->images.width, &game->images.height);
	if (!game->images.player_left_1)
			ft_error_message("Failed to load player left 1 image");


	game->images.player_left_2 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_LEFT_2,
		&game->images.width, &game->images.height);
	if (!game->images.player_left_2)
			ft_error_message("Failed to load player left 2 image");


	game->images.player_right_1 = mlx_xpm_file_to_image(game->mlx_connection, PLAYER_RIGHT_1,
		&game->images.width, &game->images.height);
	if (!game->images.player_right_1)
			ft_error_message("Failed to load player right 1 image");


	game->images.player_right_2 = mlx_xpm_file_to_image(game->mlx_connection, PLAYER_RIGHT_2,
		&game->images.width, &game->images.height);
	if (!game->images.player_right_2)
			ft_error_message("Failed to load player right 2 image");


	game->images.last_direction = KEY_D;
	game->images.step_count = 0;
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
			ft_player_images(game), x * TILE_SIZE, y * TILE_SIZE);
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

void	*ft_player_images(t_game *game)
{
	if (game->images.last_direction == KEY_W || game->images.last_direction == KEY_UP)
		{
			if (game->images.step_count % 2 == 0)
				return (game->images.player_up_1);
			return (game->images.player_up_2);
		}
		if (game->images.last_direction == KEY_S || game->images.last_direction == KEY_DOWN)
		{
			if (game->images.step_count % 2 == 0)
				return (game->images.player_down_1);
			return (game->images.player_down_2);
		}
		if (game->images.last_direction == KEY_A || game->images.last_direction == KEY_LEFT)
		{
			if (game->images.step_count % 2 == 0)
				return (game->images.player_left_1);
			return (game->images.player_left_2);
		}
		if (game->images.step_count % 2 == 0)
			return (game->images.player_right_1);
		return (game->images.player_right_2);
}