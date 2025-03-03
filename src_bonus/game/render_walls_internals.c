/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_internals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:53:11 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 13:53:44 by mbatty           ###   ########.fr       */
/*                                                                            */
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
