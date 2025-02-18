/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ctx.h											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/24 10:45:47 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 09:47:25 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "cub3d.h"

typedef struct s_maths
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
}	t_maths;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	escape;
} t_keys;

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
	char			spawn_facing;
	char			**map;
	int				map_height;
	int				map_width;
	char			*wall_tx[4];
	unsigned int	colors[2];
	 struct timeval    start_time;
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
	t_keys		keys;
}	t_ctx;

int		ctx_init(t_ctx *ctx, char *filename);
void	ctx_deinit(t_ctx *ctx);

#endif