/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:33:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 20:42:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_sprite_type(t_ctx *ctx, int i, char type)
{
	if (type == SPRITE_ENEMY)
	{
		ctx->ginfo.sprites[i].z = -30.0f;
		ctx->ginfo.sprites[i].type = enemy;
		ctx->ginfo.sprites[i].scale = 64;
		ctx->ginfo.sprites[i].tex = ctx->winfo.all_tx[ctx->ginfo.enemy_frame];
	}
	if (type == SPRITE_COLLEC)
	{
		ctx->ginfo.sprites[i].z = 0.0f;
		ctx->ginfo.sprites[i].type = collec;
		ctx->ginfo.sprites[i].scale = 32;
		ctx->ginfo.sprites[i].tex = ctx->winfo.all_tx[collec_tx];
	}
}

static void	get_sprite_pos(t_ctx *ctx, int i)
{
	int	x;
	int	y;

	x = 0;
	while (ctx->ginfo.map[x])
	{
		y = 0;
		while (ctx->ginfo.map[x][y])
		{
			if (ft_strchr(SPRITE_CHARSET, ctx->ginfo.map[x][y]))
			{
				ctx->ginfo.sprites[i].x = (y + .5f) * MAP_S;
				ctx->ginfo.sprites[i].y = (x + .5f) * MAP_S;
				ctx->ginfo.sprites[i].active = true;
				set_sprite_type(ctx, i, ctx->ginfo.map[x][y]);
				ctx->ginfo.map[x][y] = '0';
				return ;
			}
			y++;
		}
		x++;
	}
}

int	parse_sprites(t_ctx *ctx)
{
	int	i;

	i = 0;
	ctx->ginfo.sprites_count = charset_iter(ctx->ginfo.map, SPRITE_CHARSET);
	ctx->ginfo.sprites = ft_calloc(ctx->ginfo.sprites_count + 1,
			sizeof(t_sprite));
	if (!ctx->ginfo.sprites)
		return (!!print_error(ALLOC_ERROR));
	while (i < ctx->ginfo.sprites_count)
	{
		get_sprite_pos(ctx, i);
		i++;
	}
	ctx->ginfo.sprites[i].type = empty;
	return (1);
}
