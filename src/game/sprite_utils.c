/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:21:19 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/25 14:58:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_collec_on_pos(t_ctx *ctx, int x, int y)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if ((int)ctx->ginfo.sprites[i].x / 64 == x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == y / 64
			&& ctx->ginfo.sprites[i].active
			&& ctx->ginfo.sprites[i].type == collec)
			return (1);
		i++;
	}
	return (0);
}

void	collect_collectible(t_ctx *ctx, int x, int y)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if ((int)ctx->ginfo.sprites[i].x / 64 == (int)x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == (int)y / 64
			&& ctx->ginfo.sprites[i].type == collec
			&& ctx->ginfo.sprites[i].active)
		{
			ctx->ginfo.sprites[i].active = false;
			ctx->ginfo.coins++;
		}
		i++;
	}
}

int	is_enemy_on_pos(t_ctx *ctx, int x, int y, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if (sprite)
		{
			if ((int)ctx->ginfo.sprites[i].x / 64 == x / 64
				&& (int)ctx->ginfo.sprites[i].y / 64 == y / 64
				&& sprite != &ctx->ginfo.sprites[i]
				&& ctx->ginfo.sprites[i].active
				&& ctx->ginfo.sprites[i].type == enemy)
				return (1);
		}
		else if ((int)ctx->ginfo.sprites[i].x / 64 == x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == y / 64
			&& ctx->ginfo.sprites[i].active
			&& ctx->ginfo.sprites[i].type == enemy)
			return (1);
		i++;
	}
	return (0);
}

void	kill_enemy(t_ctx *ctx, int x, int y)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if ((int)ctx->ginfo.sprites[i].x / 64 == (int)x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == (int)y / 64
			&& ctx->ginfo.sprites[i].type == enemy
			&& ctx->ginfo.sprites[i].active)
			ctx->ginfo.sprites[i].active = false;
		i++;
	}
}
