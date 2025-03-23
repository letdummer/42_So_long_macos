/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldummer- <ldummer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:17:23 by ldummer-          #+#    #+#             */
/*   Updated: 2025/03/23 17:17:46 by ldummer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// COLORS
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define END_COLOR "\033[0;39m"

// LIBRARIES
#include "../minilibx-linux/mlx.h"
#include "../libft/libft/libft.h"
#include "../libft/ft_printf/libftprintf.h"
#include "../libft/get_next_line/get_next_line.h"

#include <stdbool.h>

//#include <X11/keysym.h>				//descomentar para usar no linux
#include <Carbon/Carbon.h>			// Include for event handling on macOS

typedef struct	s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_mlx_data
{
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
}	t_mlx_data;

// HANDLE_ERRORS
// Insert a message, do not need to add '\n'
void	ft_error_message(char *message);

void	ft_validate_map(char *file);

int	handle_input(int key, t_mlx_data *data);


#endif