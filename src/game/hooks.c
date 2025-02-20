/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   hooks.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 15:37:18 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/18 13:13:19 by mbatty		   ###   ########.fr	   */
/*																			*/
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
	int	x;
	int	y;
	t_ctx *ctx;

	ctx = ctx_ptr;
	mlx_get_mouse_pos(ctx->winfo.mlx, &x, &y);
	if (x != ctx->winfo.img->width / 2)
	{
		ctx->rotate_amount = ((float)ctx->mouse_diff - (float)x) / 200.f;
		ctx->mouse_diff = x;
	}
	move_player(ctx_ptr);
	render_frame(ctx_ptr);
	if (ctx->rotate_amount)
	{
		mlx_set_mouse_pos(ctx->winfo.mlx, ctx->winfo.img->width / 2, ctx->winfo.img->height / 2);
		ctx->rotate_amount = 0;
		ctx->mouse_diff = ctx->winfo.img->width / 2;
	}
}
