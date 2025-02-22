/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:37 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/22 12:40:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_ctx *ctx)
{
	t_rsquare	square_vars;
	t_points	pts;

	square_vars = init_rsquare_vars((ctx->maths.py - 16) / 4,
			(ctx->maths.px - 16) / 4, 8);
	render_square(ctx, square_vars, 0xFFFFFFFF);
	pts = init_dl_vars(ctx->maths.px / 4, ctx->maths.py / 4,
			(ctx->maths.px + ctx->maths.pdx * 8) / 4,
			(ctx->maths.py + ctx->maths.pdy * 8) / 4);
	draw_line(ctx->winfo.img, pts, 0x00FF00FF);
}

void	draw_minimap(t_ctx *ctx)
{
	int			x;
	int			y;
	t_rsquare	square_vars;

	x = -1;
	while (++x < ctx->ginfo.map_width - 1)
	{
		y = 0;
		while (y < ctx->ginfo.map_height)
		{
			if (ctx->ginfo.map[y][x] == '1')
			{
				square_vars = init_rsquare_vars((y * MAP_S) / 4,
						(x * MAP_S) / 4, 16);
				render_square(ctx, square_vars, 0xFF0000FF);
			}
			y++;
		}
	}
	draw_player(ctx);
}

void	draw_crosshair(t_ctx *ctx, int x, int y, int size)
{
	uint32_t	color;
	int			t_x;
	int			t_y;

	t_x = 0;
	while (t_x < size)
	{
		t_y = 0;
		while (t_y < size)
		{
			color = inverted_uint8_to_uint32(&ctx->winfo.img->pixels
				[((t_x + x) + ((t_y + y) * ctx->winfo.img->width)) * 4]);
			safe_put_pixel(ctx->winfo.img, t_x + x, t_y + y, color);
			t_y++;
		}
		t_x++;
	}
}

void	draw_sprite(t_ctx *ctx)
{
	float	sx = 1.5f * 64.f - ctx->maths.px;
	float	sy = 1.5f * 64.f - ctx->maths.py;
	float	sz = 20.f;

	float	CS = cos(ctx->maths.pa);
	float	SN = sin(ctx->maths.pa);

	float	a = sy * CS - sx * SN;
	float	b = sx * CS + sy * SN;

	sx = a;
	sy = b;

	sx = (sx * ((float)ctx->winfo.img->width / 2.f * tan(PI / 180.f * 60.f)) / sy) + ((float)ctx->winfo.img->width / 2.f);
	sy = (sz * (float)ctx->winfo.img->height / sy) + ((float)ctx->winfo.img->height / 2.f);

	// t_rsquare	sqvars;

	// sqvars = init_rsquare_vars(sy, sx - ((32 / 2) / (distance(1.5f * 64.f, 1.5f * 64.f, ctx->maths.px, ctx->maths.py) / 32)), );
	for (int x = 0; x < (MAP_S * 32) / distance(1.5f * 64.f, 1.5f * 64.f, ctx->maths.px, ctx->maths.py); x++)
	{
		for (int y = 0; y < (MAP_S * 32) / distance(1.5f * 64.f, 1.5f * 64.f, ctx->maths.px, ctx->maths.py); y++)
			safe_put_pixel(ctx->winfo.img, sx + x, sy + y, 0x00FFFFFF);
	}
}

void	render_frame(t_ctx *ctx)
{
	gettimeofday(&ctx->ginfo.start_time, NULL);
	draw_sky(ctx);
	draw_cubes(ctx);
	draw_minimap(ctx);
	draw_sprite(ctx);
	draw_crosshair(ctx, ctx->winfo.img->width / 2 - 2,
		ctx->winfo.img->height / 2 - 2, 4);
	draw_fps(ctx);
}
