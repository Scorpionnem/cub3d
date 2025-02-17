/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:12:01 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/17 14:18:16 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ft_safe_atoi(const char *nptr);
int		is_whitespace(char c);
void	clean_line(char *str);
int		charset_iter(char **map, char *charset);

uint32_t	uint8_to_uint32(uint8_t *pixels);

#endif