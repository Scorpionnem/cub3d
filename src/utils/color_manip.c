/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   color_manips.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 14:17:57 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/17 14:18:17 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	uint8_to_uint32(uint8_t *pixels)
{
	return ((pixels[0] << 24) | (pixels[1] << 16) | (pixels[2] << 8) | 255);
}

uint32_t	inverted_uint8_to_uint32(uint8_t *pixels)
{
	return (((255 - pixels[0]) << 24)
		| ((255 - pixels[1]) << 16) | ((255 - pixels[2]) << 8) | 255);
}
