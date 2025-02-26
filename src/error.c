/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:40:26 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 15:40:28 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*print_error(char *str)
{
	ft_putstr_fd(ERROR_NL, 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}

void	*print_error_read_file(char *str, int fd)
{
	ft_putstr_fd(ERROR_NL, 2);
	ft_putendl_fd(str, 2);
	close(fd);
	return (NULL);
}

void	*print_error_free(char *str, void *ptr)
{
	ft_putstr_fd(ERROR_NL, 2);
	ft_putendl_fd(str, 2);
	free(ptr);
	return (NULL);
}
