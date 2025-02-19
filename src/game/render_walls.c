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

int	map_x = 8;
int	map_y = 8;
int	map_s = 64;

int	map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void	calc_height_offset(t_ctx *ctx, t_cube_render *vars)
{
	vars->ca = ctx->maths.pa - vars->ra;
	if (vars->ca < 0)
		vars->ca += 2 * PI;
	if (vars->ca > 2 * PI)
		vars->ca -= 2 * PI;
	vars->dist = vars->dist * cos(vars->ca);
	vars->line_h = (map_s * (int)ctx->winfo.img->height) / vars->dist;
	if (vars->line_h > ctx->winfo.img->height)
		vars->line_h = ctx->winfo.img->height;
	vars->line_offset = (ctx->winfo.img->height / 2) - vars->line_h / 2;
}

void	choose_ray(t_cube_render *vars)
{
	uint32_t color = 0xFF0000FF;
	if (vars->ra > PI)
		color = 0xFF00FFFF;
	vars->ry = vars->hy;
	vars->rx = vars->hx;
	vars->dist = vars->dist_h;
	if (vars->dist_v < vars->dist_h)
	{
		color = 0x00FF00FF;
		if (vars->ra < P2 || vars->ra > P3)
			color = 0xFFFF00FF;
		vars->ry = vars->vy;
		vars->rx = vars->vx;
		vars->dist = vars->dist_v;
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
		draw_line(ctx->winfo.img, vars.r, vars.line_offset, vars.r, vars.line_h + vars.line_offset, 0xFFFFFFFF);
		vars.ra += DR / 8;
		check_rad(&vars.ra);
		vars.r++;
	}
}
