/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:12:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/15 17:04:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	clean_line(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (is_whitespace(str[i]))
			str[i] = '1';
		i++;
	}
}
