/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:14:10 by ldummer-          #+#    #+#             */
/*   Updated: 2025/04/11 17:37:00 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"


int	ft_init_wind(t_game *game)
{	
	if (!game || !game->mlx_connection)
		return (1);
	game->mlx_wind = mlx_new_window(game->mlx_connection,
		WIND_WIDTH, WIND_HEIGHT, "so_long");
	if (!game->mlx_wind)
		return (1);
	return (0);
}

int	handle_input(int key, t_game *game)
{
	if (key == KEY_ESC)	//53 is ESC key on macOS / XK_Escape is the ESC key in linux
	{
		ft_printf("The %d key (ESC) has been pressed\n", key);
		mlx_destroy_window(game->mlx_connection, game->mlx_wind);
		//mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
		exit(1);
	}
	ft_printf("The %d key has been pressed\n", key);
	return(0);
}

