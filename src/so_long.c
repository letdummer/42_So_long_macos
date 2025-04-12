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
	//int			fd;
	
	if(ac != 2)
		ft_error_message("Usage: ./so_long ./maps/valid/map.ber");
		
	ft_validate_map_extension(map_path);
	
/* 	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error_message("Cannot open map file");
	close(fd); */


	game = ft_init_game();
	if (!game)
		ft_error_message("Failed to initialize game.");
	
	if (ft_map_init(game, av[1]) != 0)
	{
		ft_cleanup(game);
		ft_error_message("Map initialization failed");
	}

	ft_printf("Debug: Starting game initialization\n");
	if (ft_validate_game_init(game) != 0)
	{
		ft_cleanup(game);
		ft_error_message("Game initialization failed.");
	}
	
	mlx_key_hook(game->mlx_wind, handle_input, game);
	mlx_loop(game->mlx_connection);
	ft_cleanup(game);
	return (0);
}
