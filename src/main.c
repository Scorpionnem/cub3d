/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:09:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 15:45:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_loop_hook(ctx.winfo.mlx, render_hook, &ctx);
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
