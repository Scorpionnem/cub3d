/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:38:23 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/03 11:18:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	press_secondary_keys(mlx_key_data_t keydata, t_ctx *ctx)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ctx->keys.escape = true;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		mouse_toggle(ctx);
	if (keydata.key == MLX_KEY_F3 && keydata.action == MLX_PRESS)
	{
		ctx->winfo.fps_toggle = !ctx->winfo.fps_toggle;
		if (!ctx->winfo.fps_toggle)
			if (ctx->winfo.fps)
				mlx_delete_image(ctx->winfo.mlx, ctx->winfo.fps);
	}
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
	{
		ctx->running = !ctx->running;
		if (ctx->running)
			mlx_set_mouse_pos(ctx->winfo.mlx,
				ctx->winfo.img->width / 2, ctx->winfo.img->height / 2);
	}
}

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
	press_secondary_keys(keydata, ctx);
}

static void	move_player_a_d(t_ctx *ctx)
{
	ctx->maths.pdx = cos(ctx->maths.pa + P2) * 5;
	ctx->maths.pdy = sin(ctx->maths.pa + P2) * 5;
	if (ctx->keys.d)
	{
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)ctx->maths.py / 64]
				[(int)(ctx->maths.px + ctx->maths.pdx) / 64]))
			ctx->maths.px += ctx->maths.pdx;
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map
				[(int)(ctx->maths.py + ctx->maths.pdy) / 64]
			[(int)ctx->maths.px / 64]))
			ctx->maths.py += ctx->maths.pdy;
	}
	if (ctx->keys.a)
	{
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)ctx->maths.py / 64]
				[(int)(ctx->maths.px - ctx->maths.pdx) / 64]))
			ctx->maths.px -= ctx->maths.pdx;
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map
				[(int)(ctx->maths.py - ctx->maths.pdy) / 64]
			[(int)ctx->maths.px / 64]))
			ctx->maths.py -= ctx->maths.pdy;
	}
	ctx->maths.pdx = cos(ctx->maths.pa) * 5;
	ctx->maths.pdy = sin(ctx->maths.pa) * 5;
}

static void	move_player_w_s(t_ctx *ctx)
{
	if (ctx->keys.w)
	{
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)ctx->maths.py / 64]
				[(int)(ctx->maths.px + ctx->maths.pdx) / 64]))
			ctx->maths.px += ctx->maths.pdx;
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map
				[(int)(ctx->maths.py + ctx->maths.pdy) / 64]
			[(int)ctx->maths.px / 64]))
			ctx->maths.py += ctx->maths.pdy;
	}
	if (ctx->keys.s)
	{
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)ctx->maths.py / 64]
				[(int)(ctx->maths.px - ctx->maths.pdx) / 64]))
			ctx->maths.px -= ctx->maths.pdx;
		if (ft_strchr(PERM_CHARSET, ctx->ginfo.map
				[(int)(ctx->maths.py - ctx->maths.pdy) / 64]
			[(int)ctx->maths.px / 64]))
			ctx->maths.py -= ctx->maths.pdy;
	}
	move_player_a_d(ctx);
}

void	move_player(t_ctx *ctx)
{
	if (!ctx->running)
		return ;
	move_player_mouse(ctx);
	if (ctx->keys.left)
	{
		ctx->maths.pa -= 0.1;
		if (ctx->maths.pa < 0)
			ctx->maths.pa += 2 * PI;
		ctx->maths.pdx = cos(ctx->maths.pa) * 5;
		ctx->maths.pdy = sin(ctx->maths.pa) * 5;
	}
	if (ctx->keys.right)
	{
		ctx->maths.pa += 0.1;
		if (ctx->maths.pa > 2 * PI)
			ctx->maths.pa -= 2 * PI;
		ctx->maths.pdx = cos(ctx->maths.pa) * 5;
		ctx->maths.pdy = sin(ctx->maths.pa) * 5;
	}
	move_player_w_s(ctx);
	check_angle(&ctx->maths.pa);
}
