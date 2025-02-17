/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:09:58 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/15 17:17:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse_file_internals.h"

int	get_color(t_ctx *ctx, char *line, t_id id)
{
	char		*raw_color;
	char		**raw_colors;
	t_rgb		rgb;

	if (ctx->ginfo.colors[convert_id(id)])
		return (!!print_error(DUPLICATE_COLOR));
	raw_color = get_raw_color(line);
	if (!raw_color)
		return (!!print_error(ALLOC_ERROR));
	raw_colors = ft_split(raw_color, ',');
	free(raw_color);
	if (!raw_colors)
		return (!!print_error(ALLOC_ERROR));
	if (!check_color_format(raw_colors, &rgb))
	{
		free_2d(raw_colors);
		return (!!print_error(INVALID_COLOR_FORMAT));
	}
	ctx->ginfo.colors[convert_id(id)] = (rgb.red << 24)
		| (rgb.green << 16) | (rgb.blue << 8) | 255;
	free_2d(raw_colors);
	return (1);
}

int	add_line_map(t_ctx *ctx, char *line, char *no_nl_line, char *added_walls)
{
	static int	i = 0;

	no_nl_line = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!no_nl_line)
		return (!!print_error(ALLOC_ERROR));
	if (ft_strlen(line) < (size_t)ctx->ginfo.map_width)
	{
		added_walls = ft_calloc(ctx->ginfo.map_width - ft_strlen(line) + 1, 1);
		if (!added_walls)
			return (!!print_error_free(ALLOC_ERROR, no_nl_line));	
		ft_memset(added_walls, '1', ctx->ginfo.map_width - ft_strlen(line));
		ctx->ginfo.map[i] = ft_strjoin(no_nl_line, added_walls);
		if (!ctx->ginfo.map[i])
		{
			free(added_walls);
			return (!!print_error_free(ALLOC_ERROR, no_nl_line));	
		}
		free(no_nl_line);
	}
	else
		ctx->ginfo.map[i] = no_nl_line;
	free(added_walls);
	clean_line(ctx->ginfo.map[i]);
	i++;
	return (1);
}

int	choose_method(t_ctx *ctx, char *line, t_id id)
{
	if (id >= north_tx && id <= east_tx)
		return (get_tx_path(ctx, line, id));
	if (id == floor_color || id == ceiling_color)
		return (get_color(ctx, line, id));
	if (id == other)
		return (add_line_map(ctx, line, NULL, NULL));
	return (1);
}

static int	count_map_height(t_ctx *ctx)
{
	int	i;
	int	res;
	t_id	id;

	id = other;
	res = 0;
	i = 0;
	while (ctx->file.lines[i])
	{
		id = get_line_identifier(ctx->file.lines[i]);
		if (id == other)
		{
			if (ft_strlen(ctx->file.lines[i]) > (size_t)ctx->ginfo.map_width)
				ctx->ginfo.map_width = ft_strlen(ctx->file.lines[i]);
			res++;
		}
		i++;
	}
	return (res);
}

int	parse_file(t_ctx *ctx)
{
	int		i;
	t_id	id;

	id = other;
	i = 0;
	ctx->ginfo.map_height = count_map_height(ctx);
	ctx->ginfo.map = ft_calloc(ctx->ginfo.map_height + 1, sizeof(char *));
	while (ctx->file.lines[i])
	{
		id = get_line_identifier(ctx->file.lines[i]);
		if (!choose_method(ctx, ctx->file.lines[i], id))
		{
			free(ctx->ginfo.map);
			free_tx_path(ctx);
			return (0);
		}
		i++;
	}
	return (1);
}
