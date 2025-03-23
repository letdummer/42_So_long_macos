/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:28 by ldummer-          #+#    #+#             */
/*   Updated: 2025/03/23 21:50:55 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
/* #include "../minilibx-linux/mlx.h"
#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h" */

/*
	to compile manually:
gcc ./src/so_long.c -L./mlx/minilibx_macos -lmlx -framework AppKit -framework OpenGL -o so_long

	no MAC, usar este commando:

gcc src/so_long.c -L./libft/ft_printf -lftprintf -L./minilibx-linux -lmlx -framework OpenGL -framework AppKit -o so_long
./so_long

*/

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

int	main(int ac, char **av)
{
	t_game		game;
	char		*map_path = av[1];
	int			fd;
	
	if(ac != 2)
		ft_error_message("Usage: ./so_long ./maps/map.ber");
	ft_validate_map_extension(map_path);
	fd = open(map_path, O_RDONLY);
	if (fd <= 0)
		ft_error_message("Error while reading the map content.");


	ft_initialize(&game);


	mlx_key_hook(game.mlx_wind, handle_input, &game);

	mlx_loop(game.mlx_connection);

	
	//mlx_destroy_display(game.mlx_connection);
	ft_free_images(&game);
	free(game.mlx_connection);
}

void	ft_initialize(t_game *game)
{	
	game->mlx_connection = mlx_init();
	if (game->mlx_connection == NULL)
		ft_error_message("Error on the MLX");
//		return(MLX_ERROR);
	
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