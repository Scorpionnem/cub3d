/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 13:13:17 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_square(t_ctx *ctx, int x, int y, int size, uint32_t color)
{
	for (int t_x = 0;t_x < size ; t_x++)
	{
		for (int t_y = 0;t_y < size ; t_y++)
		{
				mlx_put_pixel(ctx->winfo.img, t_y + y, t_x + x, color);
		}
	}
}

void	render_frame(t_ctx *ctx)
{
	for (int x = 0; x < SCREEN_HEIGHT; x++)
	{
		for (int y = 0; y < SCREEN_WIDTH; y++)
		{
			mlx_put_pixel(ctx->winfo.img, y, x, 0x000000FF);
		}
	}
	for (int x = 0; ctx->ginfo.map[x]; x++)
	{
		for (int y = 0; ctx->ginfo.map[x][y]; y++)
		{
			if (ctx->ginfo.map[x][y] == '1')
				render_square(ctx, x * 16, y * 16, 16, 0xFF0000FF);
		}
	}
	render_square(ctx, ctx->ginfo.x * 16, ctx->ginfo.y * 16, 16, 0x00FF00FF);
}
