/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   hooks.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 15:37:33 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/18 10:45:03 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *ctx_ptr);
void	render_hook(void *ctx_ptr);

void	press_key(mlx_key_data_t keydata, t_ctx *ctx);
void	move_player(t_ctx *ctx);

#endif