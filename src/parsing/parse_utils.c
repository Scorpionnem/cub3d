/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:25:06 by mbatty            #+#    #+#             */
/*   Updated: 2025/03/03 11:11:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_all_loaded(t_ctx *ctx)
{
	if (!ctx->ginfo.all_tx[north_tx] || !ctx->ginfo.all_tx[south_tx]
		|| !ctx->ginfo.all_tx[east_tx] || !ctx->ginfo.all_tx[west_tx]
		|| !ctx->ginfo.colors[floor_id] || !ctx->ginfo.colors[ceiling_id])
		return (0);
	return (1);
}
