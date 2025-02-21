/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:53 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 15:39:55 by mbatty           ###   ########.fr       */
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

static int	is_str_only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static int	check_sides_valid(char **map)
{
	int	y;

	y = 0;
	if (is_str_only_char(map[y], '1') == 0)
		return (0);
	while (map[y])
	{
		if (map[y][0] == '1' && map[y][ft_strlen(map[y]) - 1] == '1')
			y++;
		else
			return (0);
	}
	if (is_str_only_char(map[y - 1], '1') == 0)
		return (0);
	return (1);
}

int	parse_map(t_ctx *ctx)
{
	if (!check_valid_charset(ctx->ginfo.map, MAP_CHARSET))
		return (!!print_error(INVALID_CHARS));
	if (!check_sides_valid(ctx->ginfo.map))
		return (!!print_error(INVALID_MAP_SIDES));
	if (charset_iter(ctx->ginfo.map, PLAYER_CHARSET) != 1)
		return (!!print_error(PLAYER_COUNT_ERROR));
	get_player_pos(ctx);
	return (1);
}
