/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vertical_rays.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/19 10:38:29 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 10:47:20 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	init_vertical_rays_vars(t_ctx *ctx, t_cube_render *vars)
{
	vars->dof = 0;
	vars->dist_v = 1000000;
	vars->vx = ctx->maths.px;
	vars->vy = ctx->maths.py;
	vars->n_tan = -tan(vars->ra);
}

void	init_vertical_rays(t_ctx *ctx, t_cube_render *vars)
{
	if (vars->ra > P2 && vars->ra < P3)
	{
		vars->rx = (((int)ctx->maths.px / 64) * 64) - 0.001;
		vars->ry = (ctx->maths.px - vars->rx) * vars->n_tan + ctx->maths.py;
		vars->xo = -64;
		vars->yo = -vars->xo * vars->n_tan;
	}
	if (vars->ra < P2 || vars->ra > P3)
	{
		vars->rx = (((int)ctx->maths.px / 64) * 64) + 64;
		vars->ry = (ctx->maths.px - vars->rx) * vars->n_tan + ctx->maths.py;
		vars->xo = 64;
		vars->yo = -vars->xo * vars->n_tan;
	}
	if (vars->ra == 0 || vars->ra == PI)
	{
		vars->rx = ctx->maths.px;
		vars->ry = ctx->maths.py;
		vars->dof = 8;
	}
}

void	cast_vertical_rays(t_ctx *ctx, t_cube_render *vars)
{
	while (vars->dof < RENDER_DISTANCE)
	{
		vars->mx = (int)(vars->rx) / 64;
		vars->my = (int)(vars->ry) / 64;
		if (vars->my >= 0 && vars->mx >= 0 && vars->mx < ctx->ginfo.map_width
			&& vars->my < ctx->ginfo.map_height
			&& ctx->ginfo.map[vars->my][vars->mx] == '1')
		{
			vars->vx = vars->rx;
			vars->vy = vars->ry;
			vars->dist_v = distance(ctx->maths.px,
					ctx->maths.py, vars->vx, vars->vy);
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
