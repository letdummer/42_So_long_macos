/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:22 by ldummer-          #+#    #+#             */
/*   Updated: 2025/06/06 19:02:32 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_map_images(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
				game->images.floor, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
			if (game->map.grid[y][x] == MAP_WALL)
				ft_render_wall(game, x, y);
			else if (game->map.grid[y][x] == MAP_COLLECT)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.collectible, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
			else if (game->map.grid[y][x] == MAP_EXIT)
				render_exit(game, x, y);
			else if (game->map.grid[y][x] == MAP_PLAYER)
				mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					ft_player_images(game), x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
			x++;
		}
		y++;
	}
}

void	ft_render_wall(t_game *game, int x, int y)
{
	char	*wall_path;
	void	*temp_wall;

	wall_path = ft_walls_tiles(game, x, y);
	temp_wall = mlx_xpm_file_to_image(game->mlx_connection,
		wall_path, &game->images.width, &game->images.height);
	if (temp_wall)
	{
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			temp_wall, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
		mlx_destroy_image(game->mlx_connection, temp_wall);
	}
}

void	render_exit(t_game *game, int x, int y)
{
	void	*exit_open;

	if (game->collected_items == game->map.collectibles)
	{
		exit_open = mlx_xpm_file_to_image(game->mlx_connection, EXIT_OPEN,
			&game->images.width, &game->images.height);
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			exit_open, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
		mlx_destroy_image(game->mlx_connection, exit_open);
	}
	else
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.exit, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
}

void	ft_render_images(t_game *game)
{
	game->images.floor = mlx_xpm_file_to_image(game->mlx_connection, FLOOR,
		&game->images.width, &game->images.height);
	game->images.wall = NULL;
	game->images.collectible =  mlx_xpm_file_to_image(game->mlx_connection, COLLECTIBLE,
		&game->images.width, &game->images.height);
	game->images.exit =  mlx_xpm_file_to_image(game->mlx_connection, EXIT,
		&game->images.width, &game->images.height);
	game->images.player_up_1 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_UP_1,
		&game->images.width, &game->images.height);
	game->images.player_up_2 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_UP_2,
		&game->images.width, &game->images.height);
	game->images.player_down_1 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_DOWN_1,
		&game->images.width, &game->images.height);
	game->images.player_down_2 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_DOWN_2,
		&game->images.width, &game->images.height);		
	game->images.player_left_1 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_LEFT_1,
		&game->images.width, &game->images.height);
	game->images.player_left_2 =  mlx_xpm_file_to_image(game->mlx_connection, PLAYER_LEFT_2,
		&game->images.width, &game->images.height);
	game->images.player_right_1 = mlx_xpm_file_to_image(game->mlx_connection, PLAYER_RIGHT_1,
		&game->images.width, &game->images.height);
	game->images.player_right_2 = mlx_xpm_file_to_image(game->mlx_connection, PLAYER_RIGHT_2,
		&game->images.width, &game->images.height);
	game->images.last_direction = KEY_D;
	game->images.step_count = 0;
} 

void	ft_update_grid(t_game *game, int x, int y)
{   
	char	*wall_path;
	void	*exit_open;

	mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
		game->images.floor, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
    if (game->map.grid[y][x] == MAP_WALL)
    {
		wall_path = ft_walls_tiles(game, x, y);
		game->images.wall = mlx_xpm_file_to_image(game->mlx_connection,
			wall_path, &game->images.width, &game->images.height);
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.wall, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
		mlx_destroy_image(game->mlx_connection, game->images.wall);
    }
	if (game->map.grid[y][x] == MAP_COLLECT)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			game->images.collectible, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	if (game->map.grid[y][x] == MAP_EXIT)
	{
		if (game->collected_items == game->map.collectibles)
		{
			exit_open = mlx_xpm_file_to_image(game->mlx_connection, EXIT_OPEN,
				&game->images.width, &game->images.height);
			mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
				exit_open, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
			mlx_destroy_image(game->mlx_connection, exit_open);
		}
		else
			mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
					game->images.exit, x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
	}
	if (game->map.grid[y][x] == MAP_PLAYER)
		mlx_put_image_to_window(game->mlx_connection, game->mlx_wind,
			ft_player_images(game), x * TILE_SIZE, (y * TILE_SIZE) + HUD_HEIGHT);
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
