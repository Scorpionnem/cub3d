/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:37:24 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 17:22:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# define GREEN		"\033[0;92m"
# define RED		"\033[0;91m"
# define BASE		"\033[0m"
# define YELLOW		"\033[0;93m"

# define BOLDRED	"\033[0;91m\033[1m"

// ERROR MESSAGES
# define ERROR_NL	"Error\n"

# define PARSE_WRONG_AC			YELLOW"Wrong argument count\n"BASE
# define INVALID_CHARS			YELLOW"Invalid character in map\n"BASE
# define INVALID_FILE_NAME		YELLOW"Invalid file name\n"BASE
# define INVALID_FILE_FORMAT	YELLOW"Invalid file format\n"BASE
# define INVALID_COLOR_FORMAT	YELLOW"Invalid color format\n"BASE
# define DUPLICATE_TOKEN		YELLOW"Duplicate texture path\n"BASE
# define DUPLICATE_COLOR		YELLOW"Duplicate color\n"BASE
# define PLAYER_COUNT_ERROR		YELLOW"Invalid amount of player spawning position\n"BASE
# define INVALID_MAP_SIDES		YELLOW"Map walls are not closed\n"BASE

# define OPEN_FAIL			RED"Failed to open file\n"BASE

# define ALLOC_ERROR		BOLDRED"Fatal error allocating memory\n"BASE
# define TEXTURE_LOAD_FAIL	BOLDRED"Fatal error allocating memory: Failed to load texture\n"BASE
# define MLX_INIT_ERROR		BOLDRED"Fatal error allocating memory: Failed to init MLX\n"BASE
# define MLX_IMG_ERROR		BOLDRED"Fatal error allocating memory: Failed create an image\n"BASE

// MISC
# define CUB_NAME		"cub3D"
# define CUB_FILE		"buc."
# define PLAYER_CHARSET	"NSWE"
# define MAP_CHARSET	"01NSWE"

#endif