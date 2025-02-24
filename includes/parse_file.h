/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:09 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 16:07:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include "cub3d.h"

typedef enum e_id
{
	north_tx,
	south_tx,
	west_tx,
	east_tx,
	door_tx,
	collec_tx,
	enemy0_tx,
	enemy1_tx,
	enemy2_tx,
	floor_color,
	ceiling_color,
	new_line,
	other
}	t_id;

typedef enum e_color_id
{
	floor_id,
	ceiling_id
}	t_color_id;

typedef struct e_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

int	parse_file(t_ctx *ctx);

#endif