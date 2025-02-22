/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:37 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/22 17:25:18 by mbatty           ###   ########.fr       */
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

	//	Checks to avoid sprite being rendered when behind

	//Checks if sprite is in view of the player
	// float	vy = 6.0f * 64.f - ctx->maths.px;
	// float	vx = 6.0f * 64.f - ctx->maths.py;
	// float	atan = atan2(vy, vx) - P2;
	// float	lefta = ctx->maths.pa - 0.523599f;
	// float	righta = ctx->maths.pa + 0.523599f;
	// atan *= -1.f;
	// check_rad(&atan);
	// check_rad(&lefta);
	// check_rad(&righta);
	// printf("%f %f %f\n", atan * 180 / PI, lefta * 180 / PI, righta * 180 / PI);
	// if (lefta < righta)
	// 	if (atan < lefta || atan > righta)
	// 		return ;
	// if (righta < lefta)
	// {
	// 	if (atan > lefta && atan < 2 * PI)
	// 		return ;
	// 	else if (atan > righta && atan < 0)
	// 		return ;
	// }
	//

void	draw_sprite(t_ctx *ctx, t_sprite *sprite)
{
	float	sxx = sprite->x;
	float	syy = sprite->y;
	float	sx = sxx - ctx->maths.px;
	float	sy = syy - ctx->maths.py;
	float	sz = sprite->z;

	float	CS = cos(ctx->maths.pa);
	float	SN = sin(ctx->maths.pa);

	float	a = sy * CS - sx * SN;
	float	b = sx * CS + sy * SN;

	sx = a;
	sy = b;

	sx = (sx * ((float)ctx->winfo.img->width / 2.f * tan(PI / 180.f * 60.f)) / sy) + ((float)ctx->winfo.img->width / 2.f);
	sy = (sz * (float)ctx->winfo.img->height / sy) + ((float)ctx->winfo.img->height / 2.f);

	float	dist = distance(sxx, syy, ctx->maths.px, ctx->maths.py);
	float	line_height = (MAP_S * (int)ctx->winfo.img->height) / dist;
	float	line_width = (MAP_S * (int)ctx->winfo.img->width) / dist;
	mlx_texture_t	*tex;
	uint32_t		color;

	tex = sprite->tex;
	float	y_offset = tex->height / line_height;
	float	x_offset = tex->width / line_width;
	float	t_y = 0;
	float	t_x = 0;
	float	save_sy = sy;
	for (int x = -line_width / 2; x < (int)line_width / 2; x++)
	{
		if (sx + x > 0 && sx + x < ctx->winfo.img->width && dist < ctx->maths.depth[(int)sx + x])
		{
			t_y = 0;
			if (sy < 0)
			{
				t_y += (sy * -1) * y_offset;
				sy += sy * -1;
			}
			for (int y = 0; y < (int)line_height; y++)
			{
				if (sy + y > ctx->winfo.img->height)
					break ;
				if ((((int)t_x) + (((int)t_y) * tex->width)) * 4 < tex->width * tex->height * 4)
					color = uint8_to_uint32(&tex->pixels
						[(((int)t_x) + (((int)t_y) * tex->width)) * 4]);
				if (color != 0x000000FF)
					safe_put_pixel(ctx->winfo.img, sx + x, sy + y, color);
				t_y += y_offset;
			}
			sy = save_sy;
			t_x += x_offset;
		}
		else
			t_x += x_offset;
	}
}

void	move_enemies(t_ctx *ctx, t_sprite *sprite)
{
	if (sprite->x < ctx->maths.px && ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)sprite->y / 64]
				[(int)(sprite->x + 2.f) / 64]))
		sprite->x += 2;
	if (sprite->y < ctx->maths.py && ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)(sprite->y + 2.f) / 64]
				[(int)(sprite->x) / 64]))
		sprite->y += 2;
	if (sprite->x > ctx->maths.px && ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)sprite->y / 64]
				[(int)(sprite->x - 2.f) / 64]))
		sprite->x -= 2;
	if (sprite->y > ctx->maths.py && ft_strchr(PERM_CHARSET, ctx->ginfo.map[(int)(sprite->y - 2.f) / 64]
				[(int)(sprite->x) / 64]))
		sprite->y -= 2;
}

void	render_frame(t_ctx *ctx)
{
	gettimeofday(&ctx->ginfo.start_time, NULL);
	draw_sky(ctx);
	draw_cubes(ctx);
	// draw_minimap(ctx);
	move_enemies(ctx, &ctx->sprite);
	draw_sprite(ctx, &ctx->sprite);
	draw_crosshair(ctx, ctx->winfo.img->width / 2 - 2,
		ctx->winfo.img->height / 2 - 2, 4);
	draw_fps(ctx);
}
