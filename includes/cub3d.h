/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:40:49 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 10:38:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH 1050
# define SCREEN_HEIGHT 800

# define RENDER_DISTANCE 128

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/time.h>

# define PI 3.14159265359

// PI / 2
# define P2 1.570796

// 3 * PI / 2
# define P3 4.712389

// 1 Degre in radian
# define DR 0.0174533

# include "libft.h"
# include "get_next_line.h"

# include "MLX42.h"
# include "error.h"
# include "strings.h"
# include "ctx.h"
# include "read_file.h"
# include "parse_file.h"
# include "parse_map.h"
# include "parse_sprites.h"
# include "utils.h"
# include "textures.h"
# include "hooks.h"
# include "render.h"
# include "mouse.h"
# include "doors.h"

#endif