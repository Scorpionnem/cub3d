/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mewen.mewen@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:32:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/02/21 13:01:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# include "cub3d.h"

void	handle_mouse(t_ctx *ctx);
void	reset_mouse_handle(t_ctx *ctx);
void	mouse_toggle(t_ctx *ctx);

void	move_player_mouse(t_ctx *ctx);

#endif