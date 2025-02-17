/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_internals.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:04:50 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/15 16:14:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILE_INTERNALS_H
# define PARSE_FILE_INTERNALS_H

# include "cub3d.h"

t_color_id	convert_id(t_id id);
char		*get_raw_color(char *line);
int			check_color_format(char **raw_colors, t_rgb *rgb);
int			is_whitespace(char c);
int			get_tx_path(t_ctx *ctx, char *line, t_id id);
t_id		get_line_identifier(char *str);

#endif