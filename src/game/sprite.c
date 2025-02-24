/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:57:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 10:22:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(t_ctx *ctx, t_sprite *sprite)
{
	t_sprite_vars	vars;

	init_sprite_vars(ctx, sprite, &vars);
	if (!is_angle_in_range(vars.sprite_angle * 180 / PI,
			vars.left_angle * 180 / PI, vars.right_angle * 180 / PI))
		return ;
	while (vars.x < (int)vars.line_width / 2)
	{
		if (vars.sx + vars.x > 0 && vars.sx + vars.x < ctx->winfo.img->width
			&& vars.dist < ctx->maths.depth[(int)vars.sx + vars.x])
		{
			vars.t_y = 0;
			if (vars.sy < 0)
			{
				vars.t_y += (vars.sy * -1) * vars.y_offset;
				vars.sy += vars.sy * -1;
			}
			draw_y(ctx, &vars, vars.x);
			vars.sy = vars.save_sy;
			vars.t_x += vars.x_offset;
		}
		else
			vars.t_x += vars.x_offset;
		vars.x++;
	}
}

void	move_enemies(t_ctx *ctx, t_sprite *sprite)
{
	if (sprite->x < ctx->maths.px && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)sprite->y / 64]
			[(int)(sprite->x + 2.f) / 64]))
		sprite->x += 2;
	if (sprite->y < ctx->maths.py && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)(sprite->y + 2.f) / 64]
		[(int)(sprite->x) / 64]))
		sprite->y += 2;
	if (sprite->x > ctx->maths.px && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)sprite->y / 64]
			[(int)(sprite->x - 2.f) / 64]))
		sprite->x -= 2;
	if (sprite->y > ctx->maths.py && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)(sprite->y - 2.f) / 64]
		[(int)(sprite->x) / 64]))
		sprite->y -= 2;
}
