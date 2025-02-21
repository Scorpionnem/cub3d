/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:36:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 13:33:20 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_toggle(t_ctx *ctx)
{
	ctx->mouse.toggle = !ctx->mouse.toggle;
	if (ctx->mouse.toggle)
	{
		mlx_set_mouse_pos(ctx->winfo.mlx,
			ctx->winfo.img->width / 2, ctx->winfo.img->height / 2);
		ctx->mouse.old_x = ctx->winfo.img->width / 2;
		ctx->mouse.rotate_amount = 0;
		mlx_set_cursor_mode(ctx->winfo.mlx, MLX_MOUSE_HIDDEN);
	}
	else
	{
		mlx_set_cursor_mode(ctx->winfo.mlx, MLX_MOUSE_NORMAL);
	}
}

void	move_player_mouse(t_ctx *ctx)
{
	if (!ctx->mouse.toggle)
		return ;
	if (ctx->mouse.rotate_amount != 0)
	{
		ctx->maths.pa -= ctx->mouse.rotate_amount;
		if (ctx->maths.pa < 0)
			ctx->maths.pa += 2 * PI;
		if (ctx->maths.pa > 2 * PI)
			ctx->maths.pa -= 2 * PI;
		ctx->maths.pdx = cos(ctx->maths.pa) * 5;
		ctx->maths.pdy = sin(ctx->maths.pa) * 5;
	}
}

void	handle_mouse(t_ctx *ctx)
{
	int	x;
	int	y;

	if (!ctx->mouse.toggle)
		return ;
	mlx_get_mouse_pos(ctx->winfo.mlx, &x, &y);
	if (x != ctx->winfo.img->width / 2)
	{
		ctx->mouse.rotate_amount = ((float)ctx->mouse.old_x
				- (float)x) / 200.f;
		ctx->mouse.old_x = x;
	}
}

void	reset_mouse_handle(t_ctx *ctx)
{
	if (!ctx->mouse.toggle)
		return ;
	if (ctx->mouse.rotate_amount)
	{
		mlx_set_mouse_pos(ctx->winfo.mlx,
			ctx->winfo.img->width / 2, ctx->winfo.img->height / 2);
		ctx->mouse.rotate_amount = 0;
		ctx->mouse.old_x = ctx->winfo.img->width / 2;
	}
}
