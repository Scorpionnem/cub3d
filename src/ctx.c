/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:40:22 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/03 11:30:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ctx_deinit(t_ctx *ctx)
{
	free_2d(ctx->ginfo.map);
	free_textures(ctx);
	free_tx_path(ctx);
	if (ctx->winfo.img)
		mlx_delete_image(ctx->winfo.mlx, ctx->winfo.img);
	if (ctx->winfo.fps)
		mlx_delete_image(ctx->winfo.mlx, ctx->winfo.fps);
	if (ctx->winfo.mlx)
		mlx_terminate(ctx->winfo.mlx);
}

static void	init_nulls2(t_ctx *ctx)
{
	ctx->winfo.fps_toggle = false;
	ctx->winfo.mlx = NULL;
	ctx->winfo.img = NULL;
	ctx->running = true;
}

static void	init_nulls(t_ctx *ctx)
{
	ctx->ginfo.colors[floor_id] = 0;
	ctx->ginfo.colors[ceiling_id] = 0;
	ctx->ginfo.all_tx[north_tx] = NULL;
	ctx->ginfo.all_tx[south_tx] = NULL;
	ctx->ginfo.all_tx[east_tx] = NULL;
	ctx->ginfo.all_tx[west_tx] = NULL;
	ctx->winfo.all_tx[north_tx] = NULL;
	ctx->winfo.all_tx[south_tx] = NULL;
	ctx->winfo.all_tx[east_tx] = NULL;
	ctx->winfo.all_tx[west_tx] = NULL;
	ctx->winfo.fps = NULL;
	ctx->ginfo.map_height = 0;
	ctx->ginfo.map_width = 0;
	ctx->keys.w = false;
	ctx->keys.a = false;
	ctx->keys.s = false;
	ctx->keys.d = false;
	ctx->keys.left = false;
	ctx->keys.right = false;
	ctx->keys.escape = false;
	ctx->mouse.toggle = false;
	init_nulls2(ctx);
}

static int	init_window(t_ctx *ctx)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx->winfo.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, CUB_NAME, true);
	if (!ctx->winfo.mlx)
	{
		ctx_deinit(ctx);
		return (!!print_error(MLX_INIT_ERROR));
	}
	ctx->winfo.img = mlx_new_image(ctx->winfo.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!ctx->winfo.img)
	{
		ctx_deinit(ctx);
		return (!!print_error(MLX_IMG_ERROR));
	}
	if (mlx_image_to_window(ctx->winfo.mlx, ctx->winfo.img, 0, 0) == -1)
	{
		ctx_deinit(ctx);
		return (!!print_error(ALLOC_ERROR));
	}
	return (1);
}

int	ctx_init(t_ctx *ctx, char *filename)
{
	init_nulls(ctx);
	if (!get_file(ctx, filename))
		return (0);
	if (!parse_file(ctx))
	{
		free_2d(ctx->file.lines);
		return (0);
	}
	free_2d(ctx->file.lines);
	if (!parse_map(ctx))
	{
		free_2d(ctx->ginfo.map);
		free_tx_path(ctx);
		return (0);
	}
	if (!open_textures(ctx))
	{
		free_2d(ctx->ginfo.map);
		free_tx_path(ctx);
		free_textures(ctx);
		return (0);
	}
	return (init_window(ctx));
}
