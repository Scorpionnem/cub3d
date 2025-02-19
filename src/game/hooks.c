/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   hooks.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 15:37:18 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/18 13:13:19 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *ctx_ptr)
{
	press_key(keydata, ctx_ptr);
}

void	render_hook(void *ctx_ptr)
{
	move_player(ctx_ptr);
	render_frame(ctx_ptr);
}
