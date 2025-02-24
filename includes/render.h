/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:23 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 16:40:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define MAP_S 64

typedef struct s_line_vars
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line_vars;

typedef enum s_facing
{
	north,
	south,
	east,
	west
}	t_facing;

typedef struct s_cube_render
{
	int			r;
	int			mx;
	int			my;
	int			mp;
	int			dof;
	float		ry;
	float		rx;
	float		ra;
	float		xo;
	float		yo;
	float		dist;
	float		dist_h;
	float		dist_v;
	float		a_tan;
	float		n_tan;
	float		ca;
	float		line_h;
	float		line_offset;
	float		hx;
	float		hy;
	float		vx;
	float		vy;
	t_facing	face;
}	t_cube_render;

typedef struct s_points
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_points;

typedef struct s_draw_wall
{
	int				y;
	int				x;
	float			y_offset;
	float			t_y;
}	t_draw_wall;

typedef struct s_rsquare
{
	int				y;
	int				x;
	float			size;
}	t_rsquare;

typedef struct s_sprite_vars
{
	float			sx;
	float			sy;
	float			sz;
	float			cos_pa;
	float			sin_pa;
	float			dist_x;
	float			dist_y;
	float			dist;
	float			line_height;
	float			line_width;
	mlx_texture_t	*tex;
	uint32_t		color;
	float			y_offset;
	float			x_offset;
	float			t_x;
	float			t_y;
	float			save_sy;
	float			vy;
	float			vx;
	float			sprite_angle;
	float			left_angle;
	float			right_angle;
	int				x;
}	t_sprite_vars;

t_points	init_dl_vars(int x1, int y1, int x2, int y2);
void		draw_line(mlx_image_t *image, t_points pts, uint32_t color);

int			safe_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);
void		clear_image(mlx_image_t *img);
t_rsquare	init_rsquare_vars(int x, int y, int size);
void		render_square(t_ctx *ctx, t_rsquare vars, uint32_t color);

void		draw_sprite(t_ctx *ctx, t_sprite *sprite);
void		move_enemies(t_ctx *ctx, t_sprite *sprite);
void		init_sprite_vars(t_ctx *ctx, t_sprite *sprite, t_sprite_vars *vars);
void		draw_y(t_ctx *ctx, t_sprite_vars *vars, int x);
int			is_enemy_on_pos(t_ctx *ctx, int x, int y, t_sprite *sprite);
int			is_collec_on_pos(t_ctx *ctx, int x, int y);
void		kill_enemy(t_ctx *ctx, int x, int y);
void		collect_collectible(t_ctx *ctx, int x, int y);

void		sort_sprites(t_ctx *ctx);

void		draw_sky(t_ctx *ctx);
void		draw_cubes(t_ctx *ctx);
void		draw_fps(t_ctx *ctx);
void		render_frame(t_ctx *ctx);

void		init_vertical_rays_vars(t_ctx *ctx, t_cube_render *vars);
void		init_vertical_rays(t_ctx *ctx, t_cube_render *vars);
void		init_horizontal_rays_vars(t_ctx *ctx, t_cube_render *vars);
void		init_horizontal_rays(t_ctx *ctx, t_cube_render *vars);

void		cast_vertical_rays(t_ctx *ctx, t_cube_render *vars, char *charset);
void		cast_horizontal_rays(t_ctx *ctx,
				t_cube_render *vars, char *charset);

void		cast_horizontal_enemy(t_ctx *ctx,
				t_cube_render *vars, char *charset);
void		cast_vertical_enemy(t_ctx *ctx,
				t_cube_render *vars, char *charset);

void		calc_height_offset(t_ctx *ctx, t_cube_render *vars);
void		choose_ray(t_cube_render *vars);

#endif