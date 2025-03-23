/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:22 by ldummer-          #+#    #+#             */
/*   Updated: 2025/03/23 22:41:49 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
/* #include "../minilibx-linux/mlx.h"

#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h" */

void	ft_render_images(t_game *game)
{
	game->images.wall = mlx_xpm_file_to_image(game->mlx_connection, "assets/",
		&game->images.width, &game->images.height);
	game->images.floor = mlx_xpm_file_to_image(game->mlx_connection, "assets/",
		&game->images.width, &game->images.height);
	game->images.collectible =  mlx_xpm_file_to_image(game->mlx_connection, "assets/",
		&game->images.width, &game->images.height);
	game->images.exit =  mlx_xpm_file_to_image(game->mlx_connection, "assets/",
		&game->images.width, &game->images.height);
	game->images.player =  mlx_xpm_file_to_image(game->mlx_connection, "assets/",
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