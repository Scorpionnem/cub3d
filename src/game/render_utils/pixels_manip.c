/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:06:18 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 20:16:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	safe_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
	{
        mlx_put_pixel(image, x, y, color);
		return (1);
	}
	else
		return (0);
}

void    clear_image(mlx_image_t *img)
{
    int x;
    int y;

    x = 0;
    while (x < (int)img->width)
    {
        y = 0;
        while (y < (int)img->height)
        {
            safe_put_pixel(img, x, y, 0x000000FF);
            y++;
        }
        x++;
    }
}
