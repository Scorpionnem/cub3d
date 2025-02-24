/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:40:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 14:41:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	free_tx_path(t_ctx *ctx)
{
	if (ctx->ginfo.all_tx[north_tx])
		free(ctx->ginfo.all_tx[north_tx]);
	if (ctx->ginfo.all_tx[south_tx])
		free(ctx->ginfo.all_tx[south_tx]);
	if (ctx->ginfo.all_tx[east_tx])
		free(ctx->ginfo.all_tx[east_tx]);
	if (ctx->ginfo.all_tx[west_tx])
		free(ctx->ginfo.all_tx[west_tx]);
	if (ctx->ginfo.all_tx[door_tx])
		free(ctx->ginfo.all_tx[door_tx]);
	if (ctx->ginfo.all_tx[enemy0_tx])
		free(ctx->ginfo.all_tx[enemy0_tx]);
	if (ctx->ginfo.all_tx[enemy1_tx])
		free(ctx->ginfo.all_tx[enemy1_tx]);
	if (ctx->ginfo.all_tx[enemy2_tx])
		free(ctx->ginfo.all_tx[enemy2_tx]);
}

void	free_textures(t_ctx	*ctx)
{
	if (ctx->winfo.all_tx[north_tx])
		mlx_delete_texture(ctx->winfo.all_tx[north_tx]);
	if (ctx->winfo.all_tx[south_tx])
		mlx_delete_texture(ctx->winfo.all_tx[south_tx]);
	if (ctx->winfo.all_tx[east_tx])
		mlx_delete_texture(ctx->winfo.all_tx[east_tx]);
	if (ctx->winfo.all_tx[west_tx])
		mlx_delete_texture(ctx->winfo.all_tx[west_tx]);
	if (ctx->winfo.all_tx[door_tx])
		mlx_delete_texture(ctx->winfo.all_tx[door_tx]);
	if (ctx->winfo.all_tx[enemy0_tx])
		mlx_delete_texture(ctx->winfo.all_tx[enemy0_tx]);
	if (ctx->winfo.all_tx[enemy1_tx])
		mlx_delete_texture(ctx->winfo.all_tx[enemy1_tx]);
	if (ctx->winfo.all_tx[enemy2_tx])
		mlx_delete_texture(ctx->winfo.all_tx[enemy2_tx]);
}

int	open_textures(t_ctx *ctx)
{
	ctx->winfo.all_tx[north_tx] = mlx_load_png(ctx->ginfo.all_tx[north_tx]);
	if (!ctx->winfo.all_tx[north_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[south_tx] = mlx_load_png(ctx->ginfo.all_tx[south_tx]);
	if (!ctx->winfo.all_tx[south_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[east_tx] = mlx_load_png(ctx->ginfo.all_tx[east_tx]);
	if (!ctx->winfo.all_tx[east_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[west_tx] = mlx_load_png(ctx->ginfo.all_tx[west_tx]);
	if (!ctx->winfo.all_tx[west_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[door_tx] = mlx_load_png(ctx->ginfo.all_tx[door_tx]);
	if (!ctx->winfo.all_tx[door_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[enemy0_tx] = mlx_load_png(ctx->ginfo.all_tx[enemy0_tx]);
	if (!ctx->winfo.all_tx[enemy0_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[enemy1_tx] = mlx_load_png(ctx->ginfo.all_tx[enemy1_tx]);
	if (!ctx->winfo.all_tx[enemy1_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.all_tx[enemy2_tx] = mlx_load_png(ctx->ginfo.all_tx[enemy2_tx]);
	if (!ctx->winfo.all_tx[enemy2_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	return (parse_sprites(ctx));
}
