#include "../includes/so_long.h"
#include "../minilibx-linux/mlx.h"

#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h"

#define SIDE_LEN 500
/*
	to compile manually:
gcc ./src/so_long.c -L./mlx/minilibx_macos -lmlx -framework AppKit -framework OpenGL -o so_long

	no MAC, usar este commando:

gcc src/so_long.c -L./libft/ft_printf -lftprintf -L./mlx/minilibx_macos -lmlx -framework OpenGL -framework AppKit -o so_long
./so_long

*/


// esta funcao vai ser chamada quando uma tecla for pressionada 
// dentro da janela que esta aberta
// usar o keysym torna o codigo mais portavel, pois nao depende do arranjo do teclado  
int	handle_input(int key, t_game *game)
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

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));

	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}

int	f(int keysym, t_mlx_data *data)
{
	(void)keysym;

	mlx_put_image_to_window(data->mlx_connection, data->mlx_window, data->img.img_ptr, 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx_data	data;
	
	// inicializa a conexao com o servidor grafico
	// cria uma estrutura
	// ha alocacao de memoria com malloc, entao eh importante fazer free
	data.mlx_connection = mlx_init();
//	if (data.mlx_connection == NULL)
//		return(MLX_ERROR);
		//ft_error_message("Error on the MLX");
	
	//cria uma nova janela
	// o tamanho da janela sera dinamico em relacao ao mapa utilizado
	// ver como definir o melhor tamanho	
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

	//mlx_pixel_put(mlx_connection, mlx_wind, 250, 250, 0xFFFFFF);

	// code to create an image and get the related DATA
/* 	data.img.img_ptr = mlx_new_image(data.mlx_connection, SIDE_LEN, SIDE_LEN);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);

	ft_printf("Line_len %d <-> side_len %d\n"
		"bpp %d\n"
		"endian %d\n1", data.img.line_len, SIDE_LEN, data.img.bits_per_pixel, data.img.endian);

	mlx_key_hook(data.mlx_window, f, &data);
 */

	// HOOKS	- react to events
	// quando uma tecla eh pressionada, a fc handle_input eh executada
	// recebe o identificador da janela, um ponteiro de funcao, e a estrutura
	mlx_key_hook(data.mlx_window, handle_input, &data);

	//gerencia eventos, etc
	mlx_loop(data.mlx_connection);
	
	// XCloseDisplay() eh a funcao utilizada na fc mlx_destroy_display
	// encerra a conexao com o servidor especificado e 
	// destroi todas as janelas e recursos. Basicamente limpa todo conteudo necessario

	//mlx_destroy_display(data.mlx_connection);

	// free na estrutura que contem o display
	free(data.mlx_connection);
}