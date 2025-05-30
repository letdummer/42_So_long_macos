/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:28 by ldummer-          #+#    #+#             */
/*   Updated: 2025/05/30 10:19:29 by ldummer-         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_game		*game;
	char		*map_path = av[1];
	
	// CHECK de argumentos
	if(ac != 2)
		ft_error_message("Usage: ./so_long ./maps/map.ber");
	
	ft_validate_map_extension(map_path);
	
	game = ft_init_game();
	if (!game)
		ft_error_message("Failed to initialize game.");
	ft_map_init(game, map_path);

	// CHECK demais condicoes: qtd elementos, paredes, caminho valido
	
	// INIT janela grafica
	ft_init_wind(game);
	ft_render_images(game);
	ft_map_images(game);
	ft_display_moves(game);

	mlx_key_hook(game->mlx_wind, handle_input, game);
	mlx_hook(game->mlx_wind, 17, 0, handle_close, game);	// lida com fechar a janela no X
	//    mlx_hook(game->mlx_wind, 33, 1L<<17, handle_close, game); // Linux
	mlx_loop(game->mlx_connection);
	
	//mlx_destroy_display(game->mlx_connection);
	ft_free_images(game);
	free(game->mlx_connection);
}
