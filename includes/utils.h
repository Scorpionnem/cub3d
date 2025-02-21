/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:39 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 15:41:40 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int			ft_safe_atoi(const char *nptr);
int			is_whitespace(char c);
void		clean_line(char *str);
int			charset_iter(char **map, char *charset);
long int	get_time_usec(void);

uint32_t	uint8_to_uint32(uint8_t *pixels);
uint32_t	inverted_uint8_to_uint32(uint8_t *pixels);

float		distance(float x1, float y1, float x2, float y2);
void		check_rad(float *angle);

#endif