/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:05:43 by gyong-si          #+#    #+#             */
/*   Updated: 2023/12/15 12:36:03 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_UTILS_H
# define SO_LONG_UTILS_H


# include <unistd.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# define IMG_HEIGHT			20
# define IMG_WIDTH			20
# define TILE_SIZE			50
# define MAX_ROWS			10

# define BORDER_XPM			"assets/sprites/tree.xpm"

typedef	struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int	coins;
	int	is_exit;
}		t_data;

int	on_destroy(t_data *data);
int	on_keypress(KeySym keysym, t_data *data);
int	ft_strcmp(const char *s1, const char *s2);
int	checkfiletype(const char *filename);

#endif
