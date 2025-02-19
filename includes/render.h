/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:18 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 20:31:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_line_vars
{
	int dx;
    int dy;
    int sx;
    int sy;
    int err;
	int	e2;
} t_line_vars;

void	draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, uint32_t color);
int	safe_put_pixel(mlx_image_t *image, int x, int y, uint32_t color);
void    clear_image(mlx_image_t *img);


void	render_frame(t_ctx *ctx);



void	init();


#endif