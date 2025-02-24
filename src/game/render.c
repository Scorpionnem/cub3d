/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:37 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 13:41:16 by mbatty           ###   ########.fr       */
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
			if ((((int)t_x + x) + (((int)t_y + y) * ctx->winfo.img->width)) * 4
				< ctx->winfo.img->width * ctx->winfo.img->height * 4)
				color = inverted_uint8_to_uint32(&ctx->winfo.img->pixels
					[((t_x + x) + ((t_y + y) * ctx->winfo.img->width)) * 4]);
			safe_put_pixel(ctx->winfo.img, t_x + x, t_y + y, color);
			t_y++;
		}
		t_x++;
	}
}

static void	handle_sprites(t_ctx *ctx)
{
	int	i;

	i = 0;
	sort_sprites(ctx);
	while (i < ctx->ginfo.sprites_count)
	{
		if (ctx->ginfo.sprites[i].type == enemy)
			move_enemies(ctx, &ctx->ginfo.sprites[i]);
		draw_sprite(ctx, &ctx->ginfo.sprites[i]);
		i++;
	}
}

void	render_frame(t_ctx *ctx)
{
	if (!ctx->running)
		return ;
	gettimeofday(&ctx->ginfo.start_time, NULL);
	draw_sky(ctx);
	draw_cubes(ctx);
	// draw_minimap(ctx);
	handle_sprites(ctx);
	draw_crosshair(ctx, ctx->winfo.img->width / 2 - 2,
		ctx->winfo.img->height / 2 - 2, 4);
	draw_fps(ctx);
}
