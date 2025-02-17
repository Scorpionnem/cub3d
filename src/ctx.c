/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:45:06 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 11:29:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tx_path(t_ctx *ctx)
{
	if (ctx->ginfo.wall_tx[north_tx])
		free(ctx->ginfo.wall_tx[north_tx]);
	if (ctx->ginfo.wall_tx[south_tx])
		free(ctx->ginfo.wall_tx[south_tx]);
	if (ctx->ginfo.wall_tx[east_tx])
		free(ctx->ginfo.wall_tx[east_tx]);
	if (ctx->ginfo.wall_tx[west_tx])
		free(ctx->ginfo.wall_tx[west_tx]);
}

void	ctx_deinit(t_ctx *ctx)
{
	free_2d(ctx->ginfo.map);
	free_textures(ctx);
	free_tx_path(ctx);
}

static void	init_nulls(t_ctx *ctx)
{
	ctx->ginfo.colors[floor_id] = 0;
	ctx->ginfo.colors[ceiling_id] = 0;
	ctx->ginfo.wall_tx[north_tx] = NULL;
	ctx->ginfo.wall_tx[south_tx] = NULL;
	ctx->ginfo.wall_tx[east_tx] = NULL;
	ctx->ginfo.wall_tx[west_tx] = NULL;
	ctx->winfo.wall_tx[north_tx] = NULL;
	ctx->winfo.wall_tx[south_tx] = NULL;
	ctx->winfo.wall_tx[east_tx] = NULL;
	ctx->winfo.wall_tx[west_tx] = NULL;
	ctx->ginfo.map_height = 0;
	ctx->ginfo.map_width = 0;
}

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
	printf("Spawn X:%d Spawn Y:%d", ctx->ginfo.x, ctx->ginfo.x);
}

int	ctx_init(t_ctx *ctx, char *filename)
{
	init_nulls(ctx);
	if (!get_file(ctx, filename))
		return (0);
	if (!parse_file(ctx))
	{
		free_2d(ctx->file.lines);
		return (0);
	}
	free_2d(ctx->file.lines);
	if (!parse_map(ctx))
	{
		free_2d(ctx->ginfo.map);
		free_tx_path(ctx);
		return (0);
	}
	if (!open_textures(ctx))
	{
		free_2d(ctx->ginfo.map);
		free_tx_path(ctx);
		free_textures(ctx);
		return (0);
	}
	return (1);
}
