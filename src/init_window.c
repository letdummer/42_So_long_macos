/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/24 20:39:42 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


void	ft_init_wind(t_game *game)
{	
	setenv("OBJC_DISABLE_INITIALIZE_FORK_SAFETY", "YES", 1);	// remove uma mensagem  
	game->mlx_connection = mlx_init();
	if (game->mlx_connection == NULL)
		ft_error_message("Error on the MLX");
	
/* 	game->mlx_wind = mlx_new_window(game->mlx_connection,
		500, 500, "so_long"); */
	game->mlx_wind = mlx_new_window(game->mlx_connection,
		WIND_WIDTH, WIND_HEIGHT, "so_long");
	if (game->mlx_wind == NULL)
	{
		//mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
		//return(MLX_ERROR);
	}

	void	*img;

	img = mlx_new_image(game->mlx_connection, 500, 500);
	if (img == NULL)
		ft_error_message("Error creating the image.");
	mlx_put_image_to_window(game->mlx_connection, game->mlx_wind, img, 0, 0);
}

int	handle_input(int key, t_game *game)
{
	if (key == KEY_ESC)	//53 is ESC key on macOS / XK_Escape is the ESC key in linux
	{
		ft_printf("The %d key (ESC) has been pressed\n", key);
		handle_close(game);
		//mlx_destroy_window(game->mlx_connection, game->mlx_wind);
		//mlx_destroy_display(game->mlx_connection);
		//free(game->mlx_connection);
		//exit(1);
	}
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
	{
		ft_move_player(game, key);
		ft_printf("The %d key has been pressed\n", key);
	}
	ft_printf("The %d key has been pressed!!!\n", key);
	return(0);
}

int	handle_close(t_game *game)
{
	mlx_destroy_window(game->mlx_connection, game->mlx_wind);
	free(game->mlx_connection);
	ft_printf("Game closed by closing the window.\n");
	exit(0);
}
