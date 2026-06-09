/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:27:04 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/09 21:11:26 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err_msg(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

// void	close_window(t_game *game, t_img img)
// {
// 	mlx_destroy_image(img.ptr, img.img);
// 	mlx_destroy_window((img.ptr), img.win);
// 	mlx_loop_end(img.ptr);
// 	mlx_destroy_display(img.ptr);
// 	free(img.ptr);
// }

// void	exit_cub3d(t_game *game)
// {
// 	close_window(game, game->frame);
// 	free_parser_data(game);
// 	exit(1);
// }
