/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pixels_manip.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/18 20:06:18 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 10:48:05 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

int	safe_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
	{
		mlx_put_pixel(image, x, y, color);
		return (1);
	}
	else
		return (0);
}

void	clear_image(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < (int)img->width)
	{
		y = 0;
		while (y < (int)img->height)
		{
			safe_put_pixel(img, x, y, 0x000000FF);
			y++;
		}
		x++;
	}
}

void	draw_sky(t_ctx *ctx)
{
	int	x;
	int	y;

	x = 0;
	while (x < (int)ctx->winfo.img->width)
	{
		y = 0;
		while (y < (int)ctx->winfo.img->height)
		{
			if (y > (int)ctx->winfo.img->height / 2)
				safe_put_pixel(ctx->winfo.img, x, y,
					ctx->ginfo.colors[floor_id]);
			else
				safe_put_pixel(ctx->winfo.img, x, y,
					ctx->ginfo.colors[ceiling_id]);
			y++;
		}
		x++;
	}
}

t_rsquare	init_rsquare_vars(int x, int y, int size)
{
	t_rsquare	res;

	res.x = x;
	res.y = y;
	res.size = size;
	return (res);
}

void	render_square(t_ctx *ctx, t_rsquare vars, uint32_t color)
{
	int	t_x;
	int	t_y;

	t_x = 0;
	while (t_x < vars.size)
	{
		t_y = 0;
		while (t_y < vars.size)
		{
			safe_put_pixel(ctx->winfo.img, t_y + vars.y, t_x + vars.x, color);
			t_y++;
		}
		t_x++;
	}
}
