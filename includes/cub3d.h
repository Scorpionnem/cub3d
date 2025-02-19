/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:16 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 21:27:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 300

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

# include "libft.h"
# include "get_next_line.h"

# include "MLX42.h"
# include "error.h"
# include "strings.h"
# include "ctx.h"
# include "read_file.h"
# include "parse_file.h"
# include "parse_map.h"
# include "utils.h"
# include "textures.h"
# include "hooks.h"
# include "render.h"

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/time.h>

#endif