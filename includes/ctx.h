/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:45:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 13:42:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "cub3d.h"

typedef struct s_maths
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
	double		frame_time;
	double		rot_speed;
	double		move_speed;
	long int	color;
}	t_maths;

typedef struct s_winfo
{
	mlx_image_t		*img;
	mlx_texture_t	*wall_tx[4];
	mlx_t			*mlx;
}	t_winfo;

typedef struct s_ginfo
{
	int				x;
	int				y;
	char			**map;
	int				map_height;
	int				map_width;
	char			*wall_tx[4];
	unsigned int	colors[2];
}	t_ginfo;

typedef struct s_file
{
	char	**lines;
	int		lines_count;
}	t_file;

typedef struct s_ctx
{
	t_ginfo		ginfo;
	t_winfo		winfo;
	t_maths		maths;
	t_file		file;
}	t_ctx;

int		ctx_init(t_ctx *ctx, char *filename);
void	ctx_deinit(t_ctx *ctx);

//REMOVE ME LATER
void	print_ctx(t_ctx *ctx);
//REMOVE ME LATER

#endif