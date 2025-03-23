#include "../includes/so_long.h"
#include "../minilibx-linux/mlx.h"
#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h"

/*
	to compile manually:
gcc ./src/so_long.c -L./mlx/minilibx_macos -lmlx -framework AppKit -framework OpenGL -o so_long

	no MAC, usar este commando:

gcc src/so_long.c -L./libft/ft_printf -lftprintf -L./mlx/minilibx_macos -lmlx -framework OpenGL -framework AppKit -o so_long
./so_long

*/

int	handle_input(int key, t_mlx_data *data)
{
	if (key == 53)	//53 is ESC key on macOS / XK_Escape is the ESC key in linux
	{
		ft_printf("The %d key (ESC) has been pressed\n", key);
		mlx_destroy_window(data->mlx_connection, data->mlx_window);
		//mlx_destroy_display(data->mlx_connection);
		free(data->mlx_connection);
		exit(1);
	}
	ft_printf("The %d key has been pressed\n", key);
	return(0);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;
	char		*map_path = av[1];
	int			fd;
	
	if(ac != 2)
		ft_error_message("Usage: ./so_long ./maps/map.ber");
	ft_validate_map(map_path);





	data.mlx_connection = mlx_init();
	if (data.mlx_connection == NULL)
		ft_error_message("Error on the MLX");
//		return(MLX_ERROR);
	
	data.mlx_window = mlx_new_window(data.mlx_connection,
		500, 500, "so_long");
/* 	data.mlx_window = mlx_new_window(data.mlx_connection,
		WIND_WIDTH, WIND_HEIGHT, "so_long"); */
	if (data.mlx_window == NULL)
	{
		//mlx_destroy_display(data.mlx_connection);
		free(data.mlx_connection);
		//return(MLX_ERROR);
	}
	
	void	*img;
	char	*path = "./textures/wall_mid.xpm";
	int		img_width;
	int		img_height;
	img = mlx_xpm_file_to_image(data.mlx_connection, path, &img_height, &img_width);
	mlx_put_image_to_window(data.mlx_connection, data.mlx_window, img, 0, 0);

	mlx_key_hook(data.mlx_window, handle_input, &data);

	mlx_loop(data.mlx_connection);

	
	//mlx_destroy_display(data.mlx_connection);
	free(data.mlx_connection);
}