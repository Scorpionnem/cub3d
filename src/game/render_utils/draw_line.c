/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_line.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/18 20:03:50 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 10:41:00 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

static void	init_draw_line(t_line_vars *vars, int x1, int y1, int x2, int y2)
{
	vars->sx = -1;
	if (x1 < x2)
		vars->sx = 1;
	vars->sy = -1;
	if (y1 < y2)
		vars->sy = 1;
	vars->dx = abs(x2 - x1);
	vars->dy = abs(y2 - y1);
	vars->err = vars->dx - vars->dy;
}

void	draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, uint32_t color)
{
	t_line_vars	vars;

	init_draw_line(&vars, x1, y1, x2, y2);
	while (1)
	{
		safe_put_pixel(image, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
		vars.e2 = 2 * vars.err;
		if (vars.e2 > - vars.dy)
		{
			vars.err -= vars.dy;
			x1 += vars.sx;
		}
		if (vars.e2 < vars.dx)
		{
			vars.err += vars.dx;
			y1 += vars.sy;
		}
	}
}
