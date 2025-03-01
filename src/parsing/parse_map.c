/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/01 13:46:51 by mbatty           ###   ########.fr       */
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
				ctx->ginfo.map[x][y] = EMPTY;
				return ;
			}
			y++;
		}
		x++;
	}
}

static char	**dup_map(t_ctx *ctx)
{
	char	**temp_map;
	int		i;

	i = 0;
	temp_map = ft_calloc(ctx->ginfo.map_height + 1, sizeof(char *));
	if (!temp_map)
		return (NULL);
	while (i < ctx->ginfo.map_height)
	{
		temp_map[i] = ft_strdup(ctx->ginfo.map[i]);
		if (!temp_map[i])
			return (NULL);
		i++;
	}
	return (temp_map);
}

static void	flood_fill(char **map, int x, int y, t_ctx *ctx)
{
	if (!ctx->ginfo.valid_map)
		return ;
	if (x < 0 || y < 0
		|| x > ctx->ginfo.map_height - 1
		|| y > ctx->ginfo.map_width
		|| map[x][y] == ' ')
	{
		ctx->ginfo.valid_map = false;
		return ;
	}
	if (map[x][y] == WALL || map[x][y] == 'F')
		return ;
	map[x][y] = 'F';
	flood_fill(map, x + 1, y, ctx);
	flood_fill(map, x, y + 1, ctx);
	flood_fill(map, x - 1, y, ctx);
	flood_fill(map, x, y - 1, ctx);
}

static int	check_sides_valid(t_ctx	*ctx, char **temp_map)
{
	ctx->ginfo.valid_map = true;
	flood_fill(temp_map, ctx->ginfo.y, ctx->ginfo.x, ctx);
	if (!ctx->ginfo.valid_map)
		return (0);
	return (1);
}

int	parse_map(t_ctx *ctx)
{
	char	**temp_map;

	temp_map = dup_map(ctx);
	if (!temp_map)
		return (!!print_error(ALLOC_ERROR));
	if (charset_iter(ctx->ginfo.map, PLAYER_CHARSET) != 1)
	{
		free_2d(temp_map);
		return (!!print_error(PLAYER_COUNT_ERROR));
	}
	get_player_pos(ctx);
	if (!check_valid_charset(ctx->ginfo.map, MAP_CHARSET))
	{
		free_2d(temp_map);
		return (!!print_error(INVALID_CHARS));
	}
	if (!check_sides_valid(ctx, temp_map))
	{
		free_2d(temp_map);
		return (!!print_error(INVALID_MAP_SIDES));
	}
	free_2d(temp_map);
	return (1);
}
