/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:54:33 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/15 16:09:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(int fd)
{
	char	*str;
	int		res;
	int		allocerror;

	str = get_next_line(fd, &allocerror);
	if (allocerror)
		return (!!print_error(ALLOC_ERROR));
	res = 1;
	while (str)
	{
		free(str);
		str = get_next_line(fd, &allocerror);
		if (allocerror)
			return (!!print_error(ALLOC_ERROR));
		res++;
	}
	return (res);
}

static int	is_file_valid(char *filename)
{
	int		i;
	int		j;
	char	*cub;

	j = 0;
	cub = CUB_FILE;
	i = ft_strlen(filename) - 1;
	while (cub[j])
	{
		if (filename[i] != cub[j])
			return (0);
		i--;
		j++;
	}
	return (1);
}

static int	fill_file(t_ctx *ctx, int fd)
{
	int	allocerror;
	int	i;

	i = 0;
	while (i < ctx->file.lines_count)
	{
		ctx->file.lines[i] = get_next_line(fd, &allocerror);
		if (allocerror)
			return (!!print_error(ALLOC_ERROR));
		i++;
	}
	return (1);
}

static int	reopen(int fd, char *filename)
{
	int	res;

	res = 0;
	close(fd);
	res = open(filename, O_RDONLY);
	if (res <= 0)
		return (0);
	return (res);
}

int	get_file(t_ctx *ctx, char *filename)
{
	int		fd;

	if (!is_file_valid(filename))
		return (!!print_error(INVALID_FILE_NAME));
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (!!print_error(OPEN_FAIL));
	ctx->file.lines_count = count_lines(fd);
	if (!ctx->file.lines_count)
		return (!!print_error_read_file(ALLOC_ERROR, fd));
	ctx->file.lines = malloc(ctx->file.lines_count * sizeof(char *));
	if (!ctx->file.lines)
		return (!!print_error_read_file(ALLOC_ERROR, fd));
	fd = reopen(fd, filename);
	if (!fd)
		return (!!print_error(OPEN_FAIL));
	if (!fill_file(ctx, fd))
	{
		free_2d(ctx->file.lines);
		return (!!print_error_read_file(ALLOC_ERROR, fd));
	}
	close(fd);
	return (1);
}
