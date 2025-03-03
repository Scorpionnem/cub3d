/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:54:47 by lvan-slu          #+#    #+#             */
/*   Updated: 2025/03/03 09:54:48 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_border(t_ctx *ctx, t_minimap *vars)
{
	t_rsquare	border;

	border = init_rsquare_vars(vars->minimap_y - 2, vars->minimap_x - 2,
			(vars->view_range * 2 + 1) * 16 + 4);
	render_square(ctx, border, 0x444444FF);
}

void	draw_minimap_walls(t_ctx *ctx, t_minimap *vars, int y)
{
	int			rel_x;
	int			rel_y;
	int			x;
	t_rsquare	square;

	x = vars->start_x;
	while (x < vars->player_map_x + vars->view_range + 1)
	{
		if (x >= 0 && x < ctx->ginfo.map_width && y >= 0
			&& y < ctx->ginfo.map_height)
		{
			rel_x = (x - vars->start_x) * 16;
			rel_y = (y - vars->start_y) * 16;
			square = init_rsquare_vars(vars->minimap_y + rel_y, vars->minimap_x
					+ rel_x, 16);
			if (ctx->ginfo.map[y][x] == '1')
				render_square(ctx, square, 0xFF0000FF);
			else if (ctx->ginfo.map[y][x] == 'C')
				render_square(ctx, square, 0x87CEEB);
		}
		x++;
	}
}

void	draw_minimap_obstacles(t_ctx *ctx, t_minimap *vars)
{
	int	y;

	y = vars->start_y;
	while (y < vars->player_map_y + vars->view_range + 1)
	{
		draw_minimap_walls(ctx, vars, y);
		y++;
	}
}

void	draw_miniplayer(t_ctx *ctx, t_minimap *vars)
{
	float		map_pos_x;
	float		map_pos_y;
	float		rel_player_x;
	float		rel_player_y;
	t_rsquare	player;

	map_pos_x = ctx->maths.px / MAP_S;
	map_pos_y = ctx->maths.py / MAP_S;
	rel_player_x = (map_pos_x - (float)vars->start_x) * 16;
	rel_player_y = (map_pos_y - (float)vars->start_y) * 16;
	player = init_rsquare_vars(vars->minimap_y + rel_player_y - 4,
			vars->minimap_x + rel_player_x - 4, 8);
	render_square(ctx, player, 0xFFFFFFFF);
	vars->center_x = vars->minimap_x + rel_player_x;
	vars->center_y = vars->minimap_y + rel_player_y;
}

void	draw_minimap(t_ctx *ctx)
{
	t_minimap	vars;

	init_minimap_vars(&vars, ctx);
	draw_minimap_border(ctx, &vars);
	draw_minimap_obstacles(ctx, &vars);
	draw_miniplayer(ctx, &vars);
	cast_all_rays(ctx, &vars);
}
