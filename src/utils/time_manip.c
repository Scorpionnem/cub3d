/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   time_manip.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 15:46:08 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/17 15:46:14 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

long int	get_time_usec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec);
}
