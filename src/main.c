/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/24 10:09:47 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/19 09:53:59 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac != 2)
		return (!print_error(PARSE_WRONG_AC));
	if (!ctx_init(&ctx, av[1]))
		return (1);
	ctx.maths.pdx = 0;
	ctx.maths.pdy = 0;
	ctx.maths.px = (ctx.ginfo.x + .5) * MAP_S;
	ctx.maths.py = (ctx.ginfo.y + .5) * MAP_S;
	ctx.maths.pa = 0;
	ctx.maths.pdx = cos(ctx.maths.pa) * 5;
	ctx.maths.pdy = sin(ctx.maths.pa) * 5;
	mlx_loop_hook(ctx.winfo.mlx, render_hook, &ctx);
	mlx_key_hook(ctx.winfo.mlx, key_hook, &ctx);
	mlx_loop(ctx.winfo.mlx);
	ctx_deinit(&ctx);
}
