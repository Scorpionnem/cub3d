/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ctx.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/24 10:45:06 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/18 12:41:28 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	ctx_deinit(t_ctx *ctx)
{
	free_2d(ctx->ginfo.map);
	free_textures(ctx);
	free_tx_path(ctx);
	mlx_delete_image(ctx->winfo.mlx, ctx->winfo.img);
	mlx_terminate(ctx->winfo.mlx);
}

static void	init_nulls(t_ctx *ctx)
{
	ctx->ginfo.colors[floor_id] = 0;
	ctx->ginfo.colors[ceiling_id] = 0;
	ctx->ginfo.wall_tx[north_tx] = NULL;
	ctx->ginfo.wall_tx[south_tx] = NULL;
	ctx->ginfo.wall_tx[east_tx] = NULL;
	ctx->ginfo.wall_tx[west_tx] = NULL;
	ctx->winfo.wall_tx[north_tx] = NULL;
	ctx->winfo.wall_tx[south_tx] = NULL;
	ctx->winfo.wall_tx[east_tx] = NULL;
	ctx->winfo.wall_tx[west_tx] = NULL;
	ctx->ginfo.map_height = 0;
	ctx->ginfo.map_width = 0;
	ctx->keys.w = false;
	ctx->keys.a = false;
	ctx->keys.s = false;
	ctx->keys.d = false;
	ctx->keys.left = false;
	ctx->keys.right = false;
	ctx->keys.escape = false;
}

static int	init_window(t_ctx *ctx)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx->winfo.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, CUB_NAME, true);
	if (!ctx->winfo.mlx)
	{
		free_2d(ctx->ginfo.map);
		free_tx_path(ctx);
		free_textures(ctx);
		return (!!print_error(MLX_INIT_ERROR));
	}
	ctx->winfo.img = mlx_new_image(ctx->winfo.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!ctx->winfo.img)
	{
		mlx_terminate(ctx->winfo.mlx);
		free_2d(ctx->ginfo.map);
		free_tx_path(ctx);
		free_textures(ctx);
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
