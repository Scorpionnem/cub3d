/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:09:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 15:16:44 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define screen_width 1050
#define screen_height 800	

// static void	break_block(t_ctx *ctx)
// {
// 	int x = screen_width / 2;

// 	double camera_x = 2 * x / (float)screen_width - 1;
// 		double ray_dir_x = ctx->maths.dir_x + ctx->maths.plane_x * camera_x;
// 		double ray_dir_y = ctx->maths.dir_y + ctx->maths.plane_y * camera_x;		

// 		int	map_x = (int)ctx->maths.pos_x;
// 		int	map_y = (int)ctx->maths.pos_y;

// 		double	side_dist_x;
// 		double	side_dist_y;

// 		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
// 		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
// 		double perp_wall_dist = 0;

// 		int	step_x;
// 		int	step_y;

// 		int	hit = 0;
		
// 		if (ray_dir_x < 0)
//     	{
//     		step_x = -1;
//     		side_dist_x = (ctx->maths.pos_x - map_x) * delta_dist_x;
//     	}
//     	else
//     	{
//     		step_x = 1;
//     		side_dist_x = (map_x + 1.0 - ctx->maths.pos_x) * delta_dist_x;
//     	}
//     	if (ray_dir_y < 0)
//     	{
//     		step_y = -1;
//     		side_dist_y = (ctx->maths.pos_y - map_y) * delta_dist_y;
//     	}
//     	else
//     	{
//     		step_y = 1;
//     		side_dist_y = (map_y + 1.0 - ctx->maths.pos_y) * delta_dist_y;
//     	}
// 		int	side;

// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (ctx->ginfo.map[map_x][map_y] == '1')
// 				hit = 1;
// 		}

// 		double wall_x;
//     	if (side == 0) wall_x = ctx->maths.pos_y + perp_wall_dist * ray_dir_y;
//     	else           wall_x = ctx->maths.pos_x + perp_wall_dist * ray_dir_x;
//     	wall_x -= floor((wall_x));

// 		if (side == 0)
// 			perp_wall_dist = (side_dist_x - delta_dist_x);
//     	else
// 			perp_wall_dist = (side_dist_y - delta_dist_y);

//     	int line_height = (int)(screen_height / perp_wall_dist);

//     	int draw_start = -line_height / 2 + screen_height / 2;
//     	if (draw_start < 0)
// 			draw_start = 0;
//     	int draw_end = line_height / 2 + screen_height / 2;
//     	if (draw_end > screen_height)
// 			draw_end = screen_height;

// 		ctx->ginfo.map[map_x][map_y] = '0';
// }

long int	get_time_usec(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_usec);
}

static void	frame_loop(void *ctx_ptr)
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
      			// mlx_put_pixel(ctx->winfo.img, i, j, ctx->ginfo.colors[ceiling_id]);
      			mlx_put_pixel(ctx->winfo.img, i, j, uint8_to_uint32(&ctx->winfo.wall_tx[north_tx]->pixels[(i + (j * ctx->winfo.wall_tx[north_tx]->width)) * 4]));	
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


static void	key_hook(mlx_key_data_t keydata, void *ctx_ptr)
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

int main(int ac, char **av)
{
	t_ctx	ctx;
	if (ac != 2)
		return (!!print_error(PARSE_WRONG_AC));
	if (!ctx_init(&ctx, av[1]))
 		return (1);
	ctx.maths.pos_x = ctx.ginfo.x;
	ctx.maths.pos_y = ctx.ginfo.y;
	ctx.maths.dir_x = -1;
	ctx.maths.dir_y = 0;
	ctx.maths.plane_x = 0;
	ctx.maths.plane_y = 0.66;
	ctx.maths.time = 0;
	ctx.maths.old_time = 0;
	print_ctx(&ctx);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx.winfo.mlx = mlx_init(screen_width, screen_height, "caca3d", true);
	ctx.winfo.img = mlx_new_image(ctx.winfo.mlx, screen_width, screen_height);
	// ctx.tx = mlx_load_png("wall.png");
	// ctx.img_tx = mlx_texture_to_image(ctx.mlx, ctx.tx);
	mlx_image_to_window(ctx.winfo.mlx, ctx.winfo.img, 0, 0);
	mlx_loop_hook(ctx.winfo.mlx, frame_loop, &ctx);
	mlx_key_hook(ctx.winfo.mlx, key_hook, &ctx);
	mlx_loop(ctx.winfo.mlx);
	mlx_delete_image(ctx.winfo.mlx, ctx.winfo.img);
	mlx_terminate(ctx.winfo.mlx);
	ctx_deinit(&ctx);
}

// #include "cub3d.h"

// int	main(int ac, char **av)
// {
// 	t_ctx	ctx;

// 	if (ac != 2)
// 		return (!print_error(PARSE_WRONG_AC));
// 	if (!ctx_init(&ctx, av[1]))
// 		return (1);
// 	print_ctx(&ctx);
// 	printf("\nall good\n");
// 	ctx_deinit(&ctx);
// }
