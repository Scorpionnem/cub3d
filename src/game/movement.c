/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:38:30 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 12:43:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	press_key(mlx_key_data_t keydata, t_ctx *ctx)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		ctx->keys.w = true;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		ctx->keys.w = false;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		ctx->keys.a = true;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		ctx->keys.a = false;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		ctx->keys.s = true;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		ctx->keys.s = false;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		ctx->keys.d = true;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		ctx->keys.d = false;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		ctx->keys.left = true;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		ctx->keys.left = false;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		ctx->keys.right = true;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		ctx->keys.right = false;
}

// static void	rotate_player(t_ctx *ctx)
// {
// 	if (ctx->keys.left)
// 	{
// 		ctx->maths.plane_x -= 0.05;
// 		if (ctx->maths.plane_x < 0)
// 			ctx->maths.plane_x += 2 * PI;
// 		ctx->maths.dir_x = cos(ctx->maths.plane_x) * 5;
// 		ctx->maths.dir_y = sin(ctx->maths.plane_x) * 5;
		
// 	}
// 	if (ctx->keys.right)
// 	{		
// 		ctx->maths.plane_x += 0.05;
// 		if (ctx->maths.plane_x > 2 * PI)
// 			ctx->maths.plane_x -= 2 * PI;
// 		ctx->maths.dir_x = cos(ctx->maths.plane_x) * 5;
// 		ctx->maths.dir_y = sin(ctx->maths.plane_x) * 5;
// 	}
// }

void	move_player(t_ctx *ctx)
{
	usleep(1);

	 //move forward if no wall in front of you
    if (ctx->keys.w)
    {
      if(ctx->ginfo.map[(int)(ctx->maths.pos_x + ctx->maths.dir_x * ctx->maths.move_speed)][(int)ctx->maths.pos_y] == '0') ctx->maths.pos_x += ctx->maths.dir_x * ctx->maths.move_speed;
      if(ctx->ginfo.map[(int)ctx->maths.pos_x][(int)(ctx->maths.pos_y + ctx->maths.dir_y * ctx->maths.move_speed)] == '0') ctx->maths.pos_y += ctx->maths.dir_y * ctx->maths.move_speed;
    }
    //move backwards if no wall behind you
    if (ctx->keys.s)
    {
      if(ctx->ginfo.map[(int)(ctx->maths.pos_x - ctx->maths.dir_x * ctx->maths.move_speed)][(int)(ctx->maths.pos_y)] == '0') ctx->maths.pos_x -= ctx->maths.dir_x * ctx->maths.move_speed;
      if(ctx->ginfo.map[(int)(ctx->maths.pos_x)][(int)(ctx->maths.pos_y - ctx->maths.dir_y * ctx->maths.move_speed)] == '0') ctx->maths.pos_y -= ctx->maths.dir_y * ctx->maths.move_speed;
    }
    //rotate to the right
    if (ctx->keys.d)
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
    if (ctx->keys.a)
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
	if (ctx->keys.left)
		mlx_close_window(ctx->winfo.mlx);
}
