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

static void	init_draw_line(t_line_vars *vars, t_points pts)
{
	vars->sx = -1;
	if (pts.x1 < pts.x2)
		vars->sx = 1;
	vars->sy = -1;
	if (pts.y1 < pts.y2)
		vars->sy = 1;
	vars->dx = abs(pts.x2 - pts.x1);
	vars->dy = abs(pts.y2 - pts.y1);
	vars->err = vars->dx - vars->dy;
}

t_points	init_dl_vars(int x1, int y1, int x2, int y2)
{
	t_points	res;

	res.x1 = x1;
	res.y1 = y1;
	res.x2 = x2;
	res.y2 = y2;
	return (res);
}

void	draw_line(mlx_image_t *image, t_points pts, uint32_t color)
{
	t_line_vars	vars;

	init_draw_line(&vars, pts);
	while (1)
	{
		safe_put_pixel(image, pts.x1, pts.y1, color);
		if (pts.x1 == pts.x2 && pts.y1 == pts.y2)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 > -vars.dy)
		{
			vars.err -= vars.dy;
			pts.x1 += vars.sx;
		}
		if (vars.e2 < vars.dx)
		{
			vars.err += vars.dx;
			pts.y1 += vars.sy;
		}
	}
}
