/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:41:11 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/11 00:43:31 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_mouse_hook(t_game *game)
{
	mlx_hook(game->mlx.win, EV_MOUSEMOVE, M_MOUSEMOVE, on_mouse_move, game);
	mlx_mouse_hide(game->mlx.ptr, game->mlx.win);
	mlx_mouse_move(game->mlx.ptr, game->mlx.win, WIN_W / 2, WIN_H / 2);
}

int	on_mouse_move(int x, int y, t_game *game)
{
	int	center_x;
	int	delta_x;

	(void)y;
	center_x = WIN_W / 2;
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	game->keys.mouse_dx += delta_x;
	mlx_mouse_move(game->mlx.ptr, game->mlx.win,
		center_x, WIN_H / 2);
	return (0);
}
