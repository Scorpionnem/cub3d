/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_internals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:04:42 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/15 17:48:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_raw_color(char *line)
{
	int		i;
	char	*res;

	i = 1;
	while (line[i] && is_whitespace(line[i]))
		i++;
	res = ft_substr(line, i, ft_strlen(line) - i - 1);
	if (!res)
		return (NULL);
	return (res);
}

t_color_id	convert_id(t_id id)
{
	if (id == floor_color)
		return (floor_id);
	return (ceiling_id);
}

int	check_color_format(char **raw_colors, t_rgb *rgb)
{
	if (!raw_colors[0] || !raw_colors[1] || !raw_colors[2] || raw_colors[3])
		return (0);
	rgb->red = ft_safe_atoi(raw_colors[0]);
	rgb->green = ft_safe_atoi(raw_colors[1]);
	rgb->blue = ft_safe_atoi(raw_colors[2]);
	if (rgb->red > 255 || rgb->red < 0)
		return (0);
	if (rgb->green > 255 || rgb->green < 0)
		return (0);
	if (rgb->blue > 255 || rgb->blue < 0)
		return (0);
	return (1);
}

t_id	get_line_identifier(char *str)
{
	if (!ft_strncmp(str, "NO", 2))
		return (north_tx);
	if (!ft_strncmp(str, "SO", 2))
		return (south_tx);
	if (!ft_strncmp(str, "WE", 2))
		return (west_tx);
	if (!ft_strncmp(str, "EA", 2))
		return (east_tx);
	if (!ft_strncmp(str, "F", 1))
		return (floor_color);
	if (!ft_strncmp(str, "C", 1))
		return (ceiling_color);
	if (!ft_strncmp(str, "\n", 1))
		return (new_line);
	return (other);
}

int	get_tx_path(t_ctx *ctx, char *line, t_id id)
{
	int	i;

	i = 2;
	if (ctx->ginfo.wall_tx[id])
		return (!!print_error(DUPLICATE_TOKEN));
	while (line[i] && is_whitespace(line[i]))
		i++;
	ctx->ginfo.wall_tx[id] = ft_substr(line, i, ft_strlen(line) - i - 1);
	if (!ctx->ginfo.wall_tx[id])
		return (!!print_error(ALLOC_ERROR));
	return (1);
}
