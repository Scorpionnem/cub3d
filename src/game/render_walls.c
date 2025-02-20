/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   render_walls.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/19 10:09:42 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 10:42:22 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	calc_height_offset(t_ctx *ctx, t_cube_render *vars)
{
	vars->ca = ctx->maths.pa - vars->ra;
	if (vars->ca < 0)
		vars->ca += 2 * PI;
	if (vars->ca > 2 * PI)
		vars->ca -= 2 * PI;
	vars->dist = vars->dist * cos(vars->ca);
	vars->line_h = (MAP_S * (int)ctx->winfo.img->height) / vars->dist;
	if (vars->line_h > ctx->winfo.img->height)
		vars->line_h = ctx->winfo.img->height;
	vars->line_offset = (ctx->winfo.img->height / 2) - vars->line_h / 2;
}

void	choose_ray(t_cube_render *vars)
{
	vars->face = south;
	if (vars->ra > PI)
		vars->face = north;
	vars->ry = vars->hy;
	vars->rx = vars->hx;
	vars->dist = vars->dist_h;
	if (vars->dist_v < vars->dist_h)
	{
		vars->face = west;
		if (vars->ra < P2 || vars->ra > P3)
			vars->face = east;
		vars->ry = vars->vy;
		vars->rx = vars->vx;
		vars->dist = vars->dist_v;
	}
}

void	draw_wall_line(t_ctx *ctx, t_cube_render *vars)
{
	uint32_t		color;
	mlx_texture_t	*tex;
	int				y;
	int				x;
	float			y_offset;
	float				t_y;

	// color = 0xFFFFFFFF;
	tex = ctx->winfo.wall_tx[east_tx];
	if (vars->face == south)
		tex = ctx->winfo.wall_tx[south_tx];
		// color = 0x0000FFFF;
	if (vars->face == north)
		tex = ctx->winfo.wall_tx[north_tx];
		// color = 0xFF0000FF;
	if (vars->face == west)
		tex = ctx->winfo.wall_tx[west_tx];
		// color = 0x00FF00FF;
	y = 0;
	x = ((int)vars->rx / 2) % tex->width;
	if (vars->face == east || vars->face == west)
		x = ((int)vars->ry / 2) % tex->width;
	t_y = 0;
	y_offset = tex->height / vars->line_h;
	while (y < vars->line_h)
	{
		color = uint8_to_uint32(&tex->pixels
				[((x) + (((int)t_y) * tex->width)) * 4]);
		safe_put_pixel(ctx->winfo.img, vars->r, vars->line_offset + y, color);
		y++;
		t_y += y_offset;
	}
}

void	draw_cubes(t_ctx *ctx)
{
	t_cube_render	vars;

	vars.ra = ctx->maths.pa - DR * 30;
	check_rad(&vars.ra);
	vars.r = 0;
	while (vars.r < (int)ctx->winfo.img->width)
	{
		init_horizontal_rays_vars(ctx, &vars);
		init_horizontal_rays(ctx, &vars);
		cast_horizontal_rays(ctx, &vars);
		init_vertical_rays_vars(ctx, &vars);
		init_vertical_rays(ctx, &vars);
		cast_vertical_rays(ctx, &vars);
		choose_ray(&vars);
		calc_height_offset(ctx, &vars);
		draw_wall_line(ctx, &vars);
		draw_line(ctx->winfo.img, ctx->maths.px / 4, ctx->maths.py / 4, vars.rx / 4, vars.ry / 4, 0xFF9999FF);
		vars.ra += DR * (60 / (float)ctx->winfo.img->width);
		check_rad(&vars.ra);
		vars.r++;
	}
}
