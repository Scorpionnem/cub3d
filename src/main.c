/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:09:47 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 17:25:51 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_ctx(t_ctx *ctx)
{
	printf("Textures: \n");
	printf("North: %s\n", ctx->ginfo.wall_tx[north_tx]);
	printf("South: %s\n", ctx->ginfo.wall_tx[south_tx]);
	printf("East: %s\n", ctx->ginfo.wall_tx[east_tx]);
	printf("West: %s\n", ctx->ginfo.wall_tx[west_tx]);
	printf("\nColors: \n");
	printf("Floor: %u\n", ctx->ginfo.colors[floor_id]);
	printf("Ceiling: %u\n", ctx->ginfo.colors[ceiling_id]);
	printf("\nMap: \n");
	for (int i = 0; ctx->ginfo.map[i]; i++)
		printf("%s\n", ctx->ginfo.map[i]);
	printf("\nSpawn X:%d Spawn Y:%d Facing: %c\n", ctx->ginfo.x, ctx->ginfo.x, ctx->ginfo.spawn_facing);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2)
		return (!print_error(PARSE_WRONG_AC));
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
	mlx_loop_hook(ctx.winfo.mlx, render_hook, &ctx);
	mlx_key_hook(ctx.winfo.mlx, key_hook, &ctx);
	mlx_loop(ctx.winfo.mlx);
	ctx_deinit(&ctx);
}
