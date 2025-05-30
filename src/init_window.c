/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/30 18:26:22 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


void	ft_init_wind(t_game *game)
{	
	int window_width;
	int window_height;

	window_width = game->map.width * TILE_SIZE;
	window_height = game->map.height * TILE_SIZE;
    if (window_width > WIND_WIDTH)
        ft_error_message("Map is too wide. Maximum width is 30 tiles.");
    if (window_height > WIND_HEIGHT)
        ft_error_message("Map is too tall. Maximum height is 16 tiles.");

	setenv("OBJC_DISABLE_INITIALIZE_FORK_SAFETY", "YES", 1);	// remove uma mensagem  
	game->mlx_connection = mlx_init();
	if (game->mlx_connection == NULL)
		ft_error_message("Error on the MLX");

	game->mlx_wind = mlx_new_window(game->mlx_connection,
		window_width, window_height, "so_long");
	if (game->mlx_wind == NULL)
	{
		free(game->mlx_connection);
		ft_error_message("Error creating window");
	}
}

int	handle_input(int key, t_game *game)
{
	if (key == KEY_ESC)	//53 is ESC key on macOS / XK_Escape is the ESC key in linux
	{
		ft_printf("The %d key (ESC) has been pressed\n", key);
		handle_close(game);
	}
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)
	{
		ft_move_player(game, key);
		//ft_printf("The %d key has been pressed\n", key);
	}
	return(0);
}

