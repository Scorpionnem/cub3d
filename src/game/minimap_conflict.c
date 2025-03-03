/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_conflict.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:36:23 by lvan-slu          #+#    #+#             */
/*   Updated: 2025/03/03 11:36:24 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_ctx *ctx, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= ctx->ginfo.map_width || map_y < 0
		|| map_y >= ctx->ginfo.map_height)
		return (true);
	return (ctx->ginfo.map[map_y][map_x] == '1'
		|| ctx->ginfo.map[map_y][map_x] == 'C');
}

void	get_map_pos(t_minimap *vars, float ray_x, float ray_y, int *coords)
{
	coords[0] = (int)((ray_x - vars->minimap_x) / 16 + vars->start_x);
	coords[1] = (int)((ray_y - vars->minimap_y) / 16 + vars->start_y);
}

bool	check_ray_collision(t_ctx *ctx, t_minimap *vars, float ray_x,
		float ray_y)
{
	int		coords[2];
	int		prev_coords[2];
	float	step;

	step = 0.05f;
	get_map_pos(vars, ray_x, ray_y, coords);
	get_map_pos(vars, ray_x - step, ray_y - step, prev_coords);
	if (is_wall(ctx, coords[0], coords[1]))
		return (true);
	if (prev_coords[0] != coords[0] || prev_coords[1] != coords[1])
	{
		if (is_wall(ctx, prev_coords[0], coords[1]) || is_wall(ctx, coords[0],
				prev_coords[1]) || is_wall(ctx, prev_coords[0], prev_coords[1]))
			return (true);
	}
	return (false);
}
