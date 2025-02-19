/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/15 16:12:01 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 10:40:51 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ft_safe_atoi(const char *nptr);
int		is_whitespace(char c);
void	clean_line(char *str);
int		charset_iter(char **map, char *charset);
long int	get_time_usec(void);

uint32_t	uint8_to_uint32(uint8_t *pixels);
float	distance(float x1, float y1, float x2, float y2);
void	check_rad(float *angle);

#endif