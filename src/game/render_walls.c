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
	if (vars->ca < 0.f)
		vars->ca += 2.f * PI;
	if (vars->ca > 2.f * PI)
		vars->ca -= 2.f * PI;
	vars->dist = vars->dist * cos(vars->ca);
	vars->line_h = (MAP_S * (int)ctx->winfo.img->height) / vars->dist;
	// if (vars->line_h > ctx->winfo.img->height)
		// vars->line_h = ctx->winfo.img->height;
	vars->line_offset = (ctx->winfo.img->height / 2.f) - vars->line_h / 2.f;
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

void	draw_wall_line(t_ctx *ctx, t_cube_render *vars)
{
	uint32_t		color;
	mlx_texture_t	*tex;
	t_draw_wall		coords;

	tex = ctx->winfo.wall_tx[east_tx];
	if (vars->face == south)
		tex = ctx->winfo.wall_tx[south_tx];
	if (vars->face == north)
		tex = ctx->winfo.wall_tx[north_tx];
	if (vars->face == west)
		tex = ctx->winfo.wall_tx[west_tx];
	coords.y = 0;
	coords.x = get_x(vars, tex);
	coords.t_y = 0;
	coords.y_offset = tex->height / vars->line_h;
	while (coords.y < vars->line_h)
	{
		if (((coords.x) + (((int)coords.t_y) * tex->width)) * 4 < tex->width * tex->height * 4)
			color = uint8_to_uint32(&tex->pixels
			[((coords.x) + (((int)coords.t_y) * tex->width)) * 4]);
		safe_put_pixel(ctx->winfo.img, vars->r,
			vars->line_offset + coords.y, color);
		coords.y++;
		coords.t_y += coords.y_offset;
	}
}

void	draw_cubes(t_ctx *ctx)
{
	t_cube_render	vars;
	t_points		pts;

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
		pts = init_dl_vars(ctx->maths.px / 4, ctx->maths.py / 4,
				vars.rx / 4, vars.ry / 4);
		// draw_line(ctx->winfo.img, pts, 0xFF9999FF);
		vars.ra += DR * (60 / (float)ctx->winfo.img->width);
		check_rad(&vars.ra);
		vars.r++;
	}
}
