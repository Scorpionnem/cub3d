/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   error.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mbatty <mewen.mewen@hotmail.com>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/24 10:39:38 by mbatty			#+#	#+#			 */
/*   Updated: 2025/02/15 17:05:28 by mbatty		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	*print_error(char *str);
void	*print_error_read_file(char *str, int fd);
void	*print_error_free(char *str, void *ptr);

#endif