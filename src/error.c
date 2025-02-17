/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:40:40 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/15 17:05:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*print_error(char *str)
{
	ft_putstr_fd(ERROR_NL, 2);
	ft_putstr_fd(str, 2);
	return (NULL);
}

void	*print_error_read_file(char *str, int fd)
{
	ft_putstr_fd(ERROR_NL, 2);
	ft_putstr_fd(str, 2);
	close(fd);
	return (NULL);
}

void	*print_error_free(char *str, void *ptr)
{
	ft_putstr_fd(ERROR_NL, 2);
	ft_putstr_fd(str, 2);
	free(ptr);
	return (NULL);
}
