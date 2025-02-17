/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:37:18 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 15:43:49 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *ctx_ptr)
{
	t_ctx	*ctx;
	// int	move_speed = 1;
	// double	rot_speed = 0.05;
	ctx = ctx_ptr;

	usleep(1);

	 //move forward if no wall in front of you
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
    {
      if(ctx->ginfo.map[(int)(ctx->maths.pos_x + ctx->maths.dir_x * ctx->maths.move_speed)][(int)ctx->maths.pos_y] == '0') ctx->maths.pos_x += ctx->maths.dir_x * ctx->maths.move_speed;
      if(ctx->ginfo.map[(int)ctx->maths.pos_x][(int)(ctx->maths.pos_y + ctx->maths.dir_y * ctx->maths.move_speed)] == '0') ctx->maths.pos_y += ctx->maths.dir_y * ctx->maths.move_speed;
    }
    //move backwards if no wall behind you
    if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
    {
      if(ctx->ginfo.map[(int)(ctx->maths.pos_x - ctx->maths.dir_x * ctx->maths.move_speed)][(int)(ctx->maths.pos_y)] == '0') ctx->maths.pos_x -= ctx->maths.dir_x * ctx->maths.move_speed;
      if(ctx->ginfo.map[(int)(ctx->maths.pos_x)][(int)(ctx->maths.pos_y - ctx->maths.dir_y * ctx->maths.move_speed)] == '0') ctx->maths.pos_y -= ctx->maths.dir_y * ctx->maths.move_speed;
    }
    //rotate to the right
    if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
    {
      //both camera direction and camera plane must be rotated
      double olddir_x = ctx->maths.dir_x;
      ctx->maths.dir_x = ctx->maths.dir_x * cos(-ctx->maths.rot_speed) - ctx->maths.dir_y * sin(-ctx->maths.rot_speed);
      ctx->maths.dir_y = olddir_x * sin(-ctx->maths.rot_speed) + ctx->maths.dir_y * cos(-ctx->maths.rot_speed);
      double old_plane_x = ctx->maths.plane_x;
      ctx->maths.plane_x = ctx->maths.plane_x * cos(-ctx->maths.rot_speed) - ctx->maths.plane_y * sin(-ctx->maths.rot_speed);
      ctx->maths.plane_y = old_plane_x * sin(-ctx->maths.rot_speed) + ctx->maths.plane_y * cos(-ctx->maths.rot_speed);
    }
    //rotate to the left
    if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
    {
      //both camera direction and camera plane must be rotated
      double olddir_x = ctx->maths.dir_x;
      ctx->maths.dir_x = ctx->maths.dir_x * cos(ctx->maths.rot_speed) - ctx->maths.dir_y * sin(ctx->maths.rot_speed);
      ctx->maths.dir_y = olddir_x * sin(ctx->maths.rot_speed) + ctx->maths.dir_y * cos(ctx->maths.rot_speed);
      double old_plane_x = ctx->maths.plane_x;
      ctx->maths.plane_x = ctx->maths.plane_x * cos(ctx->maths.rot_speed) - ctx->maths.plane_y * sin(ctx->maths.rot_speed);
      ctx->maths.plane_y = old_plane_x * sin(ctx->maths.rot_speed) + ctx->maths.plane_y * cos(ctx->maths.rot_speed);
    }
	// if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		// break_block(ctx);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(ctx->winfo.mlx);
  }

void	render_hook(void *ctx_ptr)
{
	render_frame(ctx_ptr);
}
