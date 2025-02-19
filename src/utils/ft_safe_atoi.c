/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_safe_atoi.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/15 16:11:29 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/15 16:11:43 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

int	ft_safe_atoi(const char *nptr)
{
	int	i;
	int	minus_count;
	int	nb;

	nb = 0;
	minus_count = 0;
	i = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus_count++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	if ((nptr[i] < '0' && nptr[i] > '9') || (size_t)i != ft_strlen(nptr))
		return (-1);
	if (minus_count == 1)
		return (nb * -1);
	return (nb);
}
