/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:38:58 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/03 11:19:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_horizontal_rays_vars(t_ctx *ctx, t_cube_render *vars)
{
	vars->dof = 0;
	vars->dist_h = 1000000;
	vars->hx = ctx->maths.px;
	vars->hy = ctx->maths.py;
	vars->a_tan = -1 / tan(vars->ra);
}

void	init_horizontal_rays(t_ctx *ctx, t_cube_render *vars)
{
	if (vars->ra > PI)
	{
		vars->ry = (((int)ctx->maths.py / 64) * 64) - 0.001;
		vars->rx = (ctx->maths.py - vars->ry)
			* vars->a_tan + ctx->maths.px;
		vars->yo = -64;
		vars->xo = -vars->yo * vars->a_tan;
	}
	if (vars->ra < PI)
	{
		vars->ry = (((int)ctx->maths.py / 64) * 64) + 64;
		vars->rx = (ctx->maths.py - vars->ry)
			* vars->a_tan + ctx->maths.px;
		vars->yo = 64;
		vars->xo = -vars->yo * vars->a_tan;
	}
	if (vars->ra == 0 || vars->ra == PI)
	{
		vars->rx = ctx->maths.px;
		vars->ry = ctx->maths.py;
		vars->dof = 8;
	}
}

void	cast_horizontal_rays(t_ctx *ctx, t_cube_render *vars, char *charset)
{
	while (vars->dof < RENDER_DISTANCE)
	{
		vars->mx = (int)(vars->rx) / 64;
		vars->my = (int)(vars->ry) / 64;
		if (vars->my >= 0 && vars->mx >= 0 && vars->mx < ctx->ginfo.map_width
			&& vars->my < ctx->ginfo.map_height
			&& ft_strchr(charset, ctx->ginfo.map[vars->my][vars->mx]))
		{
			vars->hx = vars->rx;
			vars->hy = vars->ry;
			vars->dist_h = distance(ctx->maths.px,
					ctx->maths.py, vars->hx, vars->hy);
			vars->dof = RENDER_DISTANCE;
		}
		else
		{
			vars->rx += vars->xo;
			vars->ry += vars->yo;
			vars->dof += 1;
		}
	}
}
