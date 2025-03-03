/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:16 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/03 11:18:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_special_keys(t_ctx *ctx)
{
	if (ctx->keys.escape)
		mlx_close_window(ctx->winfo.mlx);
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
