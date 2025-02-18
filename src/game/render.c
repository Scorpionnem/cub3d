/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 16:36:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(void *ctx_ptr)
{
	t_ctx	*ctx;

	ctx = ctx_ptr;

    ctx->maths.old_time = ctx->maths.time;
    ctx->maths.time = get_time_usec();
    ctx->maths.frame_time = (ctx->maths.time - ctx->maths.old_time) / 1000.0; //frame_time is the time this frame has taken, in seconds
	if (ctx->maths.frame_time < 0)
		ctx->maths.frame_time = 16.0;
    ctx->maths.move_speed = ctx->maths.frame_time / 30; //the constant value is in squares/second
    ctx->maths.rot_speed = ctx->maths.frame_time / 400; //the constant value is in radians/second

	for (int i = 0; i < screen_width; i++)
	{
		for (int j = 0; j < screen_height; j++)
		{
			if (j < screen_height / 2)
      			mlx_put_pixel(ctx->winfo.img, i, j, ctx->ginfo.colors[ceiling_id]);
      			// mlx_put_pixel(ctx->winfo.img, i, j, uint8_to_uint32(&ctx->winfo.wall_tx[north_tx]->pixels[(i + (j * ctx->winfo.wall_tx[north_tx]->width)) * 4]));	
			else
      			mlx_put_pixel(ctx->winfo.img, i, j, ctx->ginfo.colors[floor_id]);
		}
	}
	for (int x = 0; x < screen_width; x ++)
	{
		double camera_x = 2 * x / (float)screen_width - 1;
		double ray_dir_x = ctx->maths.dir_x + ctx->maths.plane_x * camera_x;
		double ray_dir_y = ctx->maths.dir_y + ctx->maths.plane_y * camera_x;		

		int	map_x = (int)ctx->maths.pos_x;
		int	map_y = (int)ctx->maths.pos_y;

		double	side_dist_x;
		double	side_dist_y;

		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		double perp_wall_dist = 0;

		int	step_x;
		int	step_y;

		int	hit = 0;
		
		if (ray_dir_x < 0)
    	{
    		step_x = -1;
    		side_dist_x = (ctx->maths.pos_x - map_x) * delta_dist_x;
    	}
    	else
    	{
    		step_x = 1;
    		side_dist_x = (map_x + 1.0 - ctx->maths.pos_x) * delta_dist_x;
    	}
    	if (ray_dir_y < 0)
    	{
    		step_y = -1;
    		side_dist_y = (ctx->maths.pos_y - map_y) * delta_dist_y;
    	}
    	else
    	{
    		step_y = 1;
    		side_dist_y = (map_y + 1.0 - ctx->maths.pos_y) * delta_dist_y;
    	}
		int	side;

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (ctx->ginfo.map[map_x][map_y] == '1')
				hit = 1;
		}

		double wall_x;
    	if (side == 0) wall_x = ctx->maths.pos_y + perp_wall_dist * ray_dir_y;
    	else           wall_x = ctx->maths.pos_x + perp_wall_dist * ray_dir_x;
    	wall_x -= floor((wall_x));

		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
    	else
			perp_wall_dist = (side_dist_y - delta_dist_y);

    	int line_height = (int)(screen_height / perp_wall_dist);

    	int draw_start = -line_height / 2 + screen_height / 2;
    	if (draw_start < 0)
			draw_start = 0;
    	int draw_end = line_height / 2 + screen_height / 2;
    	if (draw_end > screen_height)
			draw_end = screen_height;

		long int color = rand() * ctx->ginfo.map[map_x][map_y];
		if (ctx->ginfo.map[map_x][map_y] == '1')
			color = 0x0000FFFF;
		if (ctx->ginfo.map[map_x][map_y] == 2)
			color = 0x00FF00FF;
		if (ctx->ginfo.map[map_x][map_y] == 3)
			color = 0xFF0000FF;
		if (ctx->ginfo.map[map_x][map_y] == 4)
			color = 0xFFFFFFFF;

      	if (side == 1)
			color = color / 1.5;


		for (int i = draw_start; i < draw_end; i++)
		{
      		mlx_put_pixel(ctx->winfo.img, x, i, color);
		}
    }
}
