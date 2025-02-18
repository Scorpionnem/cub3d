/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:38:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 13:13:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	press_key(mlx_key_data_t keydata, t_ctx *ctx)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		ctx->keys.w = true;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		ctx->keys.w = false;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		ctx->keys.a = true;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		ctx->keys.a = false;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		ctx->keys.s = true;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		ctx->keys.s = false;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		ctx->keys.d = true;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		ctx->keys.d = false;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ctx->keys.left = true;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		ctx->keys.left = false;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ctx->keys.right = true;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		ctx->keys.right = false;
}

void	move_player(t_ctx *ctx)
{
	if (ctx->keys.s)
	{
		if (ctx->ginfo.map[ctx->ginfo.x + 1][ctx->ginfo.y] == '1')
			return ;
		ctx->ginfo.x++;
	}
	if (ctx->keys.w)
	{
		if (ctx->ginfo.x - 1 >= 0 && ctx->ginfo.map[ctx->ginfo.x - 1][ctx->ginfo.y] == '1')
			return ;
		ctx->ginfo.x--;
	}
	if (ctx->keys.d)
	{
		if (ctx->ginfo.map[ctx->ginfo.x][ctx->ginfo.y + 1] == '1')
			return ;
		ctx->ginfo.y++;
	}
	if (ctx->keys.a)
	{
		if (ctx->ginfo.y - 1 >= 0 && ctx->ginfo.map[ctx->ginfo.x][ctx->ginfo.y - 1] == '1')
			return ;
		ctx->ginfo.y--;
	}
}
