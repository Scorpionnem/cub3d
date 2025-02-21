/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   render.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 15:33:29 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 10:45:48 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	display_fps(struct timeval start_time, int target_fps)
{
	struct timeval		end_time;
	int					start;
	int					end;

	gettimeofday(&end_time, NULL);
	start = start_time.tv_sec * 1000000 + start_time.tv_usec;
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	while (1000000 / abs(end - start + 1) > target_fps)
	{
		gettimeofday(&end_time, NULL);
		end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	}
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	printf("%d\n", 1000000 / abs(end - start + 1));
}

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

void	render_frame(t_ctx *ctx)
{
	gettimeofday(&ctx->ginfo.start_time, NULL);
	draw_sky(ctx);
	draw_cubes(ctx);
	draw_minimap(ctx);
	draw_crosshair(ctx, ctx->winfo.img->width / 2 - 2,
		ctx->winfo.img->height / 2 - 2, 4);
	display_fps(ctx->ginfo.start_time, 200);
}
