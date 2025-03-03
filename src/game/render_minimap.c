/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:54:39 by lvan-slu          #+#    #+#             */
/*   Updated: 2025/03/03 09:54:40 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap_vars(t_minimap *vars, t_ctx *ctx)
{
	vars->view_range = 8;
	vars->player_map_x = (int)(ctx->maths.px / MAP_S);
	vars->player_map_y = (int)(ctx->maths.py / MAP_S);
	vars->start_x = vars->player_map_x - vars->view_range;
	vars->start_y = vars->player_map_y - vars->view_range;
	vars->minimap_x = 20;
	vars->minimap_y = 20;
}

void	cast_single_ray(t_ctx *ctx, t_minimap *vars, float angle)
{
	float	ray[2];
	float	delta[2];
	float	dist;

	ray[0] = vars->center_x;
	ray[1] = vars->center_y;
	delta[0] = cosf(angle) * 0.02f;
	delta[1] = sinf(angle) * 0.02f;
	dist = 0;
	while (dist < 8 * vars->view_range)
	{
		if (check_ray_collision(ctx, vars, ray[0], ray[1]))
			break ;
		safe_put_pixel(ctx->winfo.img, (int)ray[0], (int)ray[1], 0x00FF00FF);
		ray[0] += delta[0];
		ray[1] += delta[1];
		dist += 0.02f;
	}
}

void	cast_all_rays(t_ctx *ctx, t_minimap *vars)
{
	int		i;
	float	angle_step;
	float	ray_angle;

	i = -32;
	angle_step = PI / 4 / 32;
	while (i < 32)
	{
		ray_angle = ctx->maths.pa + (i * angle_step);
		cast_single_ray(ctx, vars, ray_angle);
		i++;
	}
}
