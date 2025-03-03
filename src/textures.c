/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:40:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/03 11:14:52 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	free_tx_path(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i <= east_tx)
	{
		if (ctx->ginfo.all_tx[i])
			free(ctx->ginfo.all_tx[i]);
		i++;
	}
}

void	free_textures(t_ctx	*ctx)
{
	int	i;

	i = 0;
	while (i <= east_tx)
	{
		if (ctx->winfo.all_tx[i])
			mlx_delete_texture(ctx->winfo.all_tx[i]);
		i++;
	}
}

int	open_textures(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i <= east_tx)
	{
		ctx->winfo.all_tx[i] = mlx_load_png(ctx->ginfo.all_tx[i]);
		if (!ctx->winfo.all_tx[i])
			return (!!print_error(TEXTURE_LOAD_FAIL));
		i++;
	}
	return (1);
}
