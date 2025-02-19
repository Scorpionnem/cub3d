/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parse_file_internals.c							 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/15 16:04:42 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/17 10:50:09 by mbatty		   ###   ########.fr	   */
/*																			*/
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

int	get_color(t_ctx *ctx, char *line, t_id id)
{
	char		*raw_color;
	char		**raw_colors;
	t_rgb		rgb;

	if (ctx->ginfo.colors[id == ceiling_color])
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
	ctx->ginfo.colors[id == ceiling_color] = (rgb.red << 24)
		| (rgb.green << 16) | (rgb.blue << 8) | 255;
	free_2d(raw_colors);
	return (1);
}
