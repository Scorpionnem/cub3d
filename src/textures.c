/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   textures.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 11:17:26 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/17 12:05:35 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "textures.h"

void	free_tx_path(t_ctx *ctx)
{
	if (ctx->ginfo.wall_tx[north_tx])
		free(ctx->ginfo.wall_tx[north_tx]);
	if (ctx->ginfo.wall_tx[south_tx])
		free(ctx->ginfo.wall_tx[south_tx]);
	if (ctx->ginfo.wall_tx[east_tx])
		free(ctx->ginfo.wall_tx[east_tx]);
	if (ctx->ginfo.wall_tx[west_tx])
		free(ctx->ginfo.wall_tx[west_tx]);
}

void	free_textures(t_ctx	*ctx)
{
	if (ctx->winfo.wall_tx[north_tx])
		mlx_delete_texture(ctx->winfo.wall_tx[north_tx]);
	if (ctx->winfo.wall_tx[south_tx])
		mlx_delete_texture(ctx->winfo.wall_tx[south_tx]);
	if (ctx->winfo.wall_tx[east_tx])
		mlx_delete_texture(ctx->winfo.wall_tx[east_tx]);
	if (ctx->winfo.wall_tx[west_tx])
		mlx_delete_texture(ctx->winfo.wall_tx[west_tx]);
}

int	open_textures(t_ctx *ctx)
{
	ctx->winfo.wall_tx[north_tx] = mlx_load_png(ctx->ginfo.wall_tx[north_tx]);
	if (!ctx->winfo.wall_tx[north_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.wall_tx[south_tx] = mlx_load_png(ctx->ginfo.wall_tx[south_tx]);
	if (!ctx->winfo.wall_tx[south_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.wall_tx[east_tx] = mlx_load_png(ctx->ginfo.wall_tx[east_tx]);
	if (!ctx->winfo.wall_tx[east_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	ctx->winfo.wall_tx[west_tx] = mlx_load_png(ctx->ginfo.wall_tx[west_tx]);
	if (!ctx->winfo.wall_tx[west_tx])
		return (!!print_error(TEXTURE_LOAD_FAIL));
	return (1);
}
