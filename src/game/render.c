/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/18 21:32:12 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_square(t_ctx *ctx, int x, int y, int size, uint32_t color)
{
	for (int t_x = 0;t_x < size ; t_x++)
	{
		for (int t_y = 0;t_y < size ; t_y++)
		{
				safe_put_pixel(ctx->winfo.img, t_y + y, t_x + x, color);
		}
	}
}

float	px = 300;
float	py = 300;

float pdx;
float pdy;
float pa;

int	map_x = 8;
int	map_y = 8;
int	map_s = 64;



int	map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void	draw_map(t_ctx *ctx)
{
	int	x;
	int	y;
	
	for (y = 0; y < map_y; y++)
	{
		for (x = 0; x < map_x; x++)
		{
			if (map[y * map_x + x] == 1)
				render_square(ctx, y * map_s, x * map_s, 63, 0xFF0000FF);
		}
	}
}

void	move_player(t_ctx *ctx)
{
	if (ctx->keys.a)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (ctx->keys.d)
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (ctx->keys.w)
	{
		px += pdx;
		py += pdy;
	}
	if (ctx->keys.s)
	{
		px -= pdx;
		py -= pdy;
	}
}

void	init()
{
	pdx = 0;
	pdy = 0;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
}

void	draw_player(t_ctx *ctx)
{
	render_square(ctx, py - 4, px - 4, 8, 0xFFFFFFFF);
	draw_line(ctx->winfo.img, px, py, px + pdx * 5, py + pdy * 5, 0x00FF00FF);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	render_frame(t_ctx *ctx)
{
	clear_image(ctx->winfo.img);
	// draw_map(ctx);
	// draw_player(ctx);
	int	r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo;
	float	dist;

	ra = pa - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	for (r = 0; r < 480; r++)
	{
		dof = 0;
		float dist_h = 1000000,hx=px,hy=py;
		float a_tan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * a_tan + px;
			yo = -64;
			xo = -yo * a_tan;
		}
		if (ra < PI)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * a_tan + px;
			yo = 64;
			xo = -yo * a_tan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_x + mx;
			if (mp > 0 && mp < map_x * map_y && map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				dist_h = distance(px, py, hx, hy);	
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;
		float dist_v = 1000000,vx=px,vy=py;
		float n_tan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * n_tan + py;
			xo = -64;
			yo = -xo * n_tan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * n_tan + py;
			xo = 64;
			yo = -xo * n_tan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_x + mx;
			if (mp > 0 && mp < map_x * map_y && map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				dist_v = distance(px, py, vx, vy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		uint32_t color = 0xFF0000FF;
		if (ra > PI)
			color = 0xFF00FFFF;
		ry = hy;
		rx = hx;
		dist = dist_h;
		if (dist_v < dist_h)
		{
			color = 0x00FF00FF;
			if (ra < P2 || ra > P3)
				color = 0xFFFF00FF;
			ry = vy;
			rx = vx;
			dist = dist_v;
		}
		// draw_line(ctx->winfo.img, px, py, rx, ry, 0xFF0000FF);
		ra += DR / 8;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		float	ca = pa - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		dist = dist * cos(ca);
		float	line_h = (map_s * 320) / dist;
		if (line_h > 320)
			line_h = 320;
		float	line_offset = 160 - line_h / 2;
		draw_line(ctx->winfo.img, r, line_offset, r, line_h + line_offset, color);
	}
}
