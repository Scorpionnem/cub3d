/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:34 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 15:41:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "cub3d.h"

void	free_textures(t_ctx	*ctx);
int		open_textures(t_ctx *ctx);
void	free_tx_path(t_ctx *ctx);

#endif