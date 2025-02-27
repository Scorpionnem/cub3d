/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:16 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 16:44:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_special_keys(t_ctx *ctx)
{
	if (ctx->keys.escape)
		mlx_close_window(ctx->winfo.mlx);
}

void	attack_enemy(t_ctx *ctx)
{
	t_cube_render	vars;

	vars.ra = ctx->maths.pa;
	check_rad(&vars.ra);
	vars.r = 0;
	init_horizontal_rays_vars(ctx, &vars);
	init_horizontal_rays(ctx, &vars);
	cast_horizontal_enemy(ctx, &vars, DOORS_SOLID_CHARSET);
	init_vertical_rays_vars(ctx, &vars);
	init_vertical_rays(ctx, &vars);
	cast_vertical_enemy(ctx, &vars, DOORS_SOLID_CHARSET);
	choose_ray(&vars);
	if (is_enemy_on_pos(ctx, vars.rx, vars.ry, NULL))
		kill_enemy(ctx, vars.rx, vars.ry);
	if (ctx->ginfo.coins > 0)
		ctx->ginfo.coins--;
}

void	mouse_hook(enum mouse_key button, enum action action,
	enum modifier_key mod, void *ctx_ptr)
{
	t_ctx	*ctx;

	(void)mod;
	ctx = ctx_ptr;
	if (ctx->running
		&& button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		cast_door_ray(ctx_ptr);
	if (ctx->running
		&& button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& ctx->ginfo.coins)
		attack_enemy(ctx_ptr);
}

void	key_hook(mlx_key_data_t keydata, void *ctx_ptr)
{
	press_key(keydata, ctx_ptr);
	check_special_keys(ctx_ptr);
}

void	render_hook(void *ctx_ptr)
{
	handle_mouse(ctx_ptr);
	move_player(ctx_ptr);
	render_frame(ctx_ptr);
	reset_mouse_handle(ctx_ptr);
}
