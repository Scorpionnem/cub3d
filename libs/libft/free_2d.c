/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free_2d.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/15 12:56:30 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/15 13:07:13 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "stdlib.h"

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
