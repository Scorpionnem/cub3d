/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:40:33 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 14:28:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	find_face_angle(t_ctx *ctx)
{
	if (ctx->ginfo.spawn_facing == 'S')
		return (P2);
	if (ctx->ginfo.spawn_facing == 'N')
		return (P3);
	if (ctx->ginfo.spawn_facing == 'E')
		return (PI);
	return (0);
}

void	init_math_vars(t_ctx *ctx)
{
	ctx->maths.pdx = 0;
	ctx->maths.pdy = 0;
	ctx->maths.px = (ctx->ginfo.x + .5) * MAP_S;
	ctx->maths.py = (ctx->ginfo.y + .5) * MAP_S;
	ctx->maths.pa = find_face_angle(ctx);
	ctx->maths.pdx = cos(ctx->maths.pa) * 5;
	ctx->maths.pdy = sin(ctx->maths.pa) * 5;
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2)
		return (!print_error(PARSE_WRONG_AC));
	if (!ctx_init(&ctx, av[1]))
		return (1);
	init_math_vars(&ctx);
	mlx_loop_hook(ctx.winfo.mlx, render_hook, &ctx);
	mlx_key_hook(ctx.winfo.mlx, key_hook, &ctx);
	mlx_mouse_hook(ctx.winfo.mlx, mouse_hook, &ctx);
	mlx_loop(ctx.winfo.mlx);
	ctx_deinit(&ctx);
}
