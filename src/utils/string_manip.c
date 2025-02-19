/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   string_manip.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/15 16:12:45 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/17 13:40:28 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	clean_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			str[i] = '1';
		i++;
	}
}

int	charset_iter(char **map, char *charset)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(charset, map[i][j]))
				res++;
			j++;
		}
		i++;
	}
	return (res);
}
