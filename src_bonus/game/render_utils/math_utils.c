/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:38:46 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/25 14:20:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	check_rad(float *angle)
{
	if (*angle < 0)
		(*angle) += 2 * PI;
	if (*angle > 2 * PI)
		(*angle) -= 2 * PI;
}

bool	is_angle_in_range(int angle, int left, int right)
{
	left %= 360;
	right %= 360;
	angle %= 360;
	if (left > right)
		return (angle >= left || angle <= right);
	return (angle > left && angle < right);
}

void	check_angle(float *angle)
{
	if ((*angle) == 0.f || (*angle) == 2.f * (float)PI
		|| (*angle) == (float)PI || (*angle) == (float)P2)
		(*angle) += 0.001f;
	check_rad(angle);
}
