/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/25 14:27:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_x(t_cube_render *vars, mlx_texture_t *tex)
{
	int	res;

	res = (vars->rx / 64.f - floor(vars->rx / 64.f)) * ((float)tex->width);
	if (vars->face == south)
		res = (float)tex->width
			- (vars->rx / 64.f - floor(vars->rx / 64.f)) * ((float)tex->width);
	if (vars->face == east)
		res = (vars->ry / 64.f - floor(vars->ry / 64.f)) * ((float)tex->width);
	if (vars->face == west)
		res = (float)tex->width
			- (vars->ry / 64.f - floor(vars->ry / 64.f)) * ((float)tex->width);
	return (res);
}

mlx_texture_t	*choose_texture(t_ctx *ctx, t_cube_render *vars)
{
	mlx_texture_t	*res;

	res = ctx->winfo.all_tx[east_tx];
	if (vars->face == south)
		res = ctx->winfo.all_tx[south_tx];
	if (vars->face == north)
		res = ctx->winfo.all_tx[north_tx];
	if (vars->face == west)
		res = ctx->winfo.all_tx[west_tx];
	if (ctx->maths.type == closed_door)
		res = ctx->winfo.all_tx[door_tx];
	return (res);
}

void	draw_wall_line(t_ctx *ctx, t_cube_render *vars)
{
	uint32_t		color;
	mlx_texture_t	*tex;
	t_draw_wall		coords;

	coords.y = -1;
	coords.t_y = 0;
	tex = choose_texture(ctx, vars);
	coords.x = get_x(vars, tex);
	coords.y_offset = tex->height / vars->line_h;
	if (vars->line_offset < 0)
	{
		coords.t_y = coords.y_offset * (vars->line_offset * -1);
		vars->line_offset = 0;
	}
	while (++coords.y < vars->line_h
		&& coords.y + vars->line_offset < ctx->winfo.img->height)
	{
		if (((coords.x) + (((int)coords.t_y) * tex->width))
			* 4 < tex->width * tex->height * 4)
			color = uint8_to_uint32(&tex->pixels
				[((coords.x) + (((int)coords.t_y) * tex->width)) * 4]);
		safe_put_pixel(ctx->winfo.img, vars->r,
			vars->line_offset + coords.y, color);
		coords.t_y += coords.y_offset;
	}
}

static void	get_wall_type(t_ctx *ctx, t_cube_render *vars)
{
	if (ctx->ginfo.map[(int)(vars->ry / 64.f)][(int)(vars->rx / 64.f)] == 'C')
		ctx->maths.type = closed_door;
	else
		ctx->maths.type = normal_wall;
}

void	draw_cubes(t_ctx *ctx)
{
	t_cube_render	vars;
	t_points		pts;

	vars.ra = ctx->maths.pa - DR * 30;
	check_rad(&vars.ra);
	vars.r = -1;
	while (++vars.r < (int)ctx->winfo.img->width)
	{
		init_horizontal_rays_vars(ctx, &vars);
		init_horizontal_rays(ctx, &vars);
		cast_horizontal_rays(ctx, &vars, SOLID_CHARSET);
		init_vertical_rays_vars(ctx, &vars);
		init_vertical_rays(ctx, &vars);
		cast_vertical_rays(ctx, &vars, SOLID_CHARSET);
		choose_ray(&vars);
		ctx->maths.depth[vars.r] = vars.dist;
		get_wall_type(ctx, &vars);
		calc_height_offset(ctx, &vars);
		draw_wall_line(ctx, &vars);
		pts = init_dl_vars(ctx->maths.px / 4, ctx->maths.py / 4,
				vars.rx / 4, vars.ry / 4);
		vars.ra += DR * (60 / (float)ctx->winfo.img->width);
		check_rad(&vars.ra);
	}
}
