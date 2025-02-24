/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:57:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 16:43:45 by mbatty           ###   ########.fr       */
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

int	is_collec_on_pos(t_ctx *ctx, int x, int y)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if ((int)ctx->ginfo.sprites[i].x / 64 == x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == y / 64
			&& ctx->ginfo.sprites[i].active
			&& ctx->ginfo.sprites[i].type == collec)
			return (1);
		i++;
	}
	return (0);
}

void		collect_collectible(t_ctx *ctx, int x, int y)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if ((int)ctx->ginfo.sprites[i].x / 64 == (int)x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == (int)y / 64
			&& ctx->ginfo.sprites[i].type == collec
			&& ctx->ginfo.sprites[i].active)
		{
			ctx->ginfo.sprites[i].active = false;
			ctx->ginfo.coins++;
		}
		i++;
	}
}

int	is_enemy_on_pos(t_ctx *ctx, int x, int y, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if (sprite)
		{
			if ((int)ctx->ginfo.sprites[i].x / 64 == x / 64
				&& (int)ctx->ginfo.sprites[i].y / 64 == y / 64
				&& sprite != &ctx->ginfo.sprites[i]
				&& ctx->ginfo.sprites[i].active
				&& ctx->ginfo.sprites[i].type == enemy)
				return (1);
		}
		else if ((int)ctx->ginfo.sprites[i].x / 64 == x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == y / 64
			&& ctx->ginfo.sprites[i].active
			&& ctx->ginfo.sprites[i].type == enemy)
			return (1);
		i++;
	}
	return (0);
}

void	kill_enemy(t_ctx *ctx, int x, int y)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if ((int)ctx->ginfo.sprites[i].x / 64 == (int)x / 64
			&& (int)ctx->ginfo.sprites[i].y / 64 == (int)y / 64
			&& ctx->ginfo.sprites[i].type == enemy
			&& ctx->ginfo.sprites[i].active)
			ctx->ginfo.sprites[i].active = false;
		i++;
	}
}

void	move_enemies(t_ctx *ctx, t_sprite *sprite)
{
	if (sprite->x < ctx->maths.px && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)sprite->y / 64]
			[(int)(sprite->x + 2.1f) / 64])
			&& !is_enemy_on_pos(ctx, (int)sprite->x + 2.1f,
			(int)sprite->y, sprite))
		sprite->x += 2.1f;
	if (sprite->y < ctx->maths.py && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)(sprite->y + 2.1f) / 64]
		[(int)(sprite->x) / 64])
		&& !is_enemy_on_pos(ctx, (int)sprite->x,
		(int)sprite->y + 2.1f, sprite))
		sprite->y += 2.1f;
	if (sprite->x > ctx->maths.px && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)sprite->y / 64]
			[(int)(sprite->x - 2.1f) / 64])
			&& !is_enemy_on_pos(ctx, (int)sprite->x - 2.1f,
			(int)sprite->y, sprite))
		sprite->x -= 2.1f;
	if (sprite->y > ctx->maths.py && ft_strchr(PERM_CHARSET,
			ctx->ginfo.map[(int)(sprite->y - 2.1f) / 64]
		[(int)(sprite->x) / 64])
		&& !is_enemy_on_pos(ctx, (int)sprite->x,
		(int)sprite->y - 2.1f, sprite))
		sprite->y -= 2.1f;
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp.x = a->x;
	temp.y = a->y;
	temp.z = a->z;
	temp.type = a->type;
	temp.tex = a->tex;
	temp.active = a->active;
	temp.scale = a->scale;
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
	a->type = b->type;
	a->tex = b->tex;
	a->active = b->active;
	a->scale = b->scale;
	b->x = temp.x;
	b->y = temp.y;
	b->z = temp.z;
	b->type = temp.type;
	b->tex = temp.tex;
	b->active = temp.active;
	b->scale = temp.scale;
}

void	sort_sprites(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->ginfo.sprites_count)
	{
		if (ctx->ginfo.sprites[i + 1].type != empty
			&& distance(ctx->ginfo.sprites[i].x,
				ctx->ginfo.sprites[i].y, ctx->maths.px, ctx->maths.py)
			< distance(ctx->ginfo.sprites[i + 1].x,
				ctx->ginfo.sprites[i + 1].y, ctx->maths.px, ctx->maths.py))
		{
			swap_sprites(&ctx->ginfo.sprites[i], &ctx->ginfo.sprites[i + 1]);
			i = 0;
		}
		i++;
	}
}
