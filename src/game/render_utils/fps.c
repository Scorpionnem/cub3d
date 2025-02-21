/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:48:00 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 15:48:54 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*display_fps(t_ctx *ctx, struct timeval start_time, int target_fps)
{
	struct timeval		end_time;
	int					start;
	int					end;
	mlx_image_t			*res;
	char				*str;

	res = NULL;
	gettimeofday(&end_time, NULL);
	start = start_time.tv_sec * 1000000 + start_time.tv_usec;
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	while (1000000 / abs(end - start + 1) > target_fps)
	{
		gettimeofday(&end_time, NULL);
		end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	}
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	str = ft_itoa(1000000 / abs(end - start + 1));
	if (!str)
		return (print_error(ALLOC_ERROR));
	res = mlx_put_string(ctx->winfo.mlx, str, 0, 0);
	if (!res)
		return (print_error(MLX_IMG_ERROR));
	free(str);
	return (res);
}

void	draw_fps(t_ctx *ctx)
{
	if (ctx->winfo.fps_toggle)
	{
		if (ctx->winfo.fps)
			mlx_delete_image(ctx->winfo.mlx, ctx->winfo.fps);
		ctx->winfo.fps = display_fps(ctx, ctx->ginfo.start_time, 200);
		if (!ctx->winfo.fps)
			mlx_close_window(ctx->winfo.mlx);
	}
}
