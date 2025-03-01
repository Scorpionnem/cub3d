/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/01 14:53:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_map.h"

static int	check_valid_charset(char **map, char *charset)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(charset, map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	get_player_pos(t_ctx *ctx)
{
	int	x;
	int	y;

	x = 0;
	while (ctx->ginfo.map[x])
	{
		y = 0;
		while (ctx->ginfo.map[x][y])
		{
			if (ft_strchr(PLAYER_CHARSET, ctx->ginfo.map[x][y]))
			{
				ctx->ginfo.spawn_facing = ctx->ginfo.map[x][y];
				ctx->ginfo.x = y;
				ctx->ginfo.y = x;
				ctx->ginfo.map[x][y] = '0';
				return ;
			}
			y++;
		}
		x++;
	}
}

static int	check_around(t_ctx *ctx, int i, int j)
{
	if (i + 1 > 0 && j > 0
		&& i + 1 < ctx->ginfo.map_height
		&& j < ctx->ginfo.map_width)
		if (!ft_strchr(MAP_CHARSET, ctx->ginfo.map[i + 1][j]))
			return (0);
	if (i - 1 > 0 && j > 0
		&& i - 1 < ctx->ginfo.map_height
		&& j < ctx->ginfo.map_width)
		if (!ft_strchr(MAP_CHARSET, ctx->ginfo.map[i - 1][j]))
			return (0);
	if (i > 0 && j + 1 > 0
		&& i < ctx->ginfo.map_height
		&& j + 1 < ctx->ginfo.map_width)
		if (!ft_strchr(MAP_CHARSET, ctx->ginfo.map[i][j + 1]))
			return (0);
	if (i > 0 && j - 1 > 0
		&& i < ctx->ginfo.map_height
		&& j - 1 < ctx->ginfo.map_width)
		if (!ft_strchr(MAP_CHARSET, ctx->ginfo.map[i][j - 1]))
			return (0);
	return (1);
}

static int	check_sides_valid(t_ctx *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (ctx->ginfo.map[i])
	{
		j = 0;
		while (ctx->ginfo.map[i][j])
		{
			if (ft_strchr(NOT_WALL_CHARSET, ctx->ginfo.map[i][j]))
				if (!check_around(ctx, i, j))
					return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(t_ctx *ctx)
{
	if (!check_valid_charset(ctx->ginfo.map, MAP_CHARSET_SPACE))
		return (!!print_error(INVALID_CHARS));
	if (!check_sides_valid(ctx))
		return (!!print_error(INVALID_MAP_SIDES));
	if (charset_iter(ctx->ginfo.map, PLAYER_CHARSET) != 1)
		return (!!print_error(PLAYER_COUNT_ERROR));
	get_player_pos(ctx);
	return (1);
}
