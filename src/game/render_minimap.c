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

bool	check_ray_collision(t_ctx *ctx, t_minimap *vars, float ray_x,
		float ray_y)
{
	int		map_x;
	int		map_y;
	float	cell_x;
	float	cell_y;

	map_x = (int)((ray_x - vars->minimap_x) / 16 + vars->start_x);
	map_y = (int)((ray_y - vars->minimap_y) / 16 + vars->start_y);
	if (map_x < 0 || map_x >= ctx->ginfo.map_width || map_y < 0
		|| map_y >= ctx->ginfo.map_height)
		return (false);
	if (ctx->ginfo.map[map_y][map_x] != '1'
		&& ctx->ginfo.map[map_y][map_x] != 'C')
		return (false);
	cell_x = (ray_x - vars->minimap_x) - ((map_x - vars->start_x) * 16);
	cell_y = (ray_y - vars->minimap_y) - ((map_y - vars->start_y) * 16);
	return (cell_x >= 0 && cell_x <= 16 && cell_y >= 0 && cell_y <= 16);
}

void	cast_single_ray(t_ctx *ctx, t_minimap *vars, float angle)
{
	float	ray_pos[2];
	float	delta[2];
	float	dist;

	ray_pos[0] = vars->center_x;
	ray_pos[1] = vars->center_y;
	delta[0] = cosf(angle) * 0.2f;
	delta[1] = sinf(angle) * 0.2f;
	dist = 0;
	while (dist < 10 * vars->view_range)
	{
		if (check_ray_collision(ctx, vars, ray_pos[0], ray_pos[1]))
			break ;
		safe_put_pixel(ctx->winfo.img, (int)ray_pos[0], (int)ray_pos[1],
			0x00FF00FF);
		ray_pos[0] += delta[0];
		ray_pos[1] += delta[1];
		dist += 0.2f;
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
