/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_internals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:12:27 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 16:34:55 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_pos(t_ctx *ctx, t_sprite *sprite, t_sprite_vars *vars)
{
	vars->sx = sprite->x - ctx->maths.px;
	vars->sy = sprite->y - ctx->maths.py;
	vars->sz = sprite->z;
	vars->t_y = 0;
	vars->t_x = 0;
}

static void	init_angles(t_ctx *ctx, t_sprite *sprite, t_sprite_vars *vars)
{
	vars->vy = sprite->x - ctx->maths.px;
	vars->vx = sprite->y - ctx->maths.py;
	vars->sprite_angle = atan2(vars->vy, vars->vx) - P2;
	vars->left_angle = ctx->maths.pa - 0.523599f;
	vars->right_angle = ctx->maths.pa + 0.523599f;
	vars->sprite_angle *= -1.f;
	check_rad(&vars->sprite_angle);
	check_rad(&vars->left_angle);
	check_rad(&vars->right_angle);
}

void	init_sprite_vars(t_ctx *ctx, t_sprite *sprite, t_sprite_vars *vars)
{
	init_pos(ctx, sprite, vars);
	vars->cos_pa = cos(ctx->maths.pa);
	vars->sin_pa = sin(ctx->maths.pa);
	vars->dist_x = vars->sy * vars->cos_pa - vars->sx * vars->sin_pa;
	vars->dist_y = vars->sx * vars->cos_pa + vars->sy * vars->sin_pa;
	vars->sx = vars->dist_x;
	vars->sy = vars->dist_y;
	vars->sx = (vars->sx * ((float)ctx->winfo.img->width / 2.f
				* tan(PI / 180.f * 60.f)) / vars->sy)
		+ ((float)ctx->winfo.img->width / 2.f);
	vars->sy = (vars->sz * (float)ctx->winfo.img->height / vars->sy)
		+ ((float)ctx->winfo.img->height / 2.f);
	vars->dist = distance(sprite->x, sprite->y, ctx->maths.px, ctx->maths.py);
	vars->line_height = (sprite->scale
			* (int)ctx->winfo.img->height) / vars->dist;
	vars->line_width = (sprite->scale
			* (int)ctx->winfo.img->width) / vars->dist;
	vars->tex = sprite->tex;
	vars->y_offset = vars->tex->height / vars->line_height;
	vars->x_offset = vars->tex->width / vars->line_width;
	vars->save_sy = vars->sy;
	init_angles(ctx, sprite, vars);
	vars->x = -vars->line_width / 2;
}

void	draw_y(t_ctx *ctx, t_sprite_vars *vars, int x)
{
	int	y;

	y = 0;
	while (y < (int)vars->line_height)
	{
		if (vars->sy + y > ctx->winfo.img->height)
			break ;
		if ((((int)vars->t_x) + (((int)vars->t_y) * vars->tex->width))
			* 4 < vars->tex->width * vars->tex->height * 4)
			vars->color = adv_uint8_to_uint32(&vars->tex->pixels
				[(((int)vars->t_x) + (((int)vars->t_y)
							* vars->tex->width)) * 4]);
		if (vars->color != 0x00000000)
			safe_put_pixel(ctx->winfo.img, vars->sx + x,
				vars->sy + y, vars->color);
		vars->t_y += vars->y_offset;
		y++;
	}
}
