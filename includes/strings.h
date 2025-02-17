/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:37:24 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 13:42:55 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

// ERROR MESSAGES
# define ERROR_NL "Error\n"

# define MLX_INIT_FAILED "MLX initialisation failed\n"
# define PARSE_WRONG_AC "Wrong argument count\n"
# define MLX_IMAGE_FAILED "Failed to create image\n"
# define OPEN_FAIL "Failed to open file\n"
# define ALLOC_ERROR "Error allocating memory\n"
# define INVALID_FILE_NAME "Invalid file name\n"
# define INVALID_FILE_FORMAT "Invalid file format\n"
# define INVALID_COLOR_FORMAT "Invalid color format\n"
# define DUPLICATE_TOKEN "Duplicate texture path\n"
# define DUPLICATE_COLOR "Duplicate color\n"
# define PLAYER_COUNT_ERROR "Invalid amount of player spawning position\n"
# define INVALID_MAP_SIDES "Map walls are not closed\n"
# define TEXTURE_LOAD_FAIL "Failed to load texture\n"
# define INVALID_CHARS "Invalid character in map\n"

// MISC
# define CUB_NAME "cub3D"
# define CUB_FILE "buc."
# define PLAYER_CHARSET "NSEW"
# define MAP_CHARSET "10NSWE"

#endif