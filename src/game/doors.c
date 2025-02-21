/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:11:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 17:41:16 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_door_ray(t_ctx *ctx)
{
	t_cube_render	vars;

	vars.ra = ctx->maths.pa;
	check_rad(&vars.ra);
	vars.r = 0;
	init_horizontal_rays_vars(ctx, &vars);
	init_horizontal_rays(ctx, &vars);
	cast_horizontal_rays(ctx, &vars, DOORS_SOLID_CHARSET);
	init_vertical_rays_vars(ctx, &vars);
	init_vertical_rays(ctx, &vars);
	cast_vertical_rays(ctx, &vars, DOORS_SOLID_CHARSET);
	choose_ray(&vars);
	if (ctx->ginfo.map[(int)(vars.ry / 64.f)]
			[(int)(vars.rx / 64.f)] == '1')
		return ;
	if ((int)(vars.ry / 64.f) != (int)(ctx->maths.py / 64.f)
		|| (int)(vars.rx / 64.f) != (int)(ctx->maths.px / 64.f))
	{
		if (ctx->ginfo.map[(int)(vars.ry / 64.f)]
			[(int)(vars.rx / 64.f)] == 'C')
			ctx->ginfo.map[(int)(vars.ry / 64.f)][(int)(vars.rx / 64.f)] = 'O';
		else
			ctx->ginfo.map[(int)(vars.ry / 64.f)]
			[(int)(vars.rx / 64.f)] = 'C';
	}
}
