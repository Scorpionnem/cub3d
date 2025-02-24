/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/24 16:18:57 by mbatty           ###   ########.fr       */
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

# define PARSE_WRONG_AC			"\033[0;93mWrong argument count\033[0m"
# define INVALID_CHARS			"\033[0;93mInvalid character in map\033[0m"
# define INVALID_FILE_NAME		"\033[0;93mInvalid file name\033[0m"
# define INVALID_FILE_FORMAT	"\033[0;93mInvalid file format\033[0m"
# define INVALID_COLOR_FORMAT	"\033[0;93mInvalid color format\033[0m"
# define DUPLICATE_TOKEN		"\033[0;93mDuplicate texture path\033[0m"
# define DUPLICATE_COLOR		"\033[0;93mDuplicate color\033[0m"
# define PLAYER_COUNT_ERROR \
	"\033[0;93mInvalid amount of player spawning position\033[0m"
# define INVALID_MAP_SIDES		"\033[0;93mMap walls are not closed\033[0m"

# define OPEN_FAIL			"\033[0;91mFailed to open file\033[0m"

# define ALLOC_ERROR \
"\033[0;91m\033[1mFatal error allocating memory\033[0m"
# define TEXTURE_LOAD_FAIL \
"\033[0;91m\033[1mFatal error allocating memory: Failed to load texture\033[0m"
# define MLX_INIT_ERROR \
"\033[0;91m\033[1mFatal error allocating memory: Failed to init MLX\033[0m"
# define MLX_IMG_ERROR \
"\033[0;91m\033[1mFatal error allocating memory: Failed create an image\033[0m"

// MISC
# define CUB_NAME		"cub3D"
# define CUB_FILE		"buc."
# define PLAYER_CHARSET	"NSWE"
# define SPRITE_CHARSET	"XD"
# define MAP_CHARSET	"01NSWEOCXD"

# define SPRITE_ENEMY	'X'
# define SPRITE_COLLEC	'D'

//Permeable (not solid)
# define PERM_CHARSET			"0O"
# define SOLID_CHARSET			"1C"
# define DOORS_CHARSET			"OC"
# define DOORS_SOLID_CHARSET	"OC1"

#endif