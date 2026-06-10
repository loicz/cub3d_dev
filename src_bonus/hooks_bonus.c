/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:39:57 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/11 00:47:11 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key_state(int keycode, t_game *game, int state)
{
	if (keycode == KEY_W)
		game->keys.w = state;
	else if (keycode == KEY_A)
		game->keys.a = state;
	else if (keycode == KEY_S)
		game->keys.s = state;
	else if (keycode == KEY_D)
		game->keys.d = state;
	else if (keycode == KEY_LEFT)
		game->keys.left = state;
	else if (keycode == KEY_RIGHT)
		game->keys.right = state;
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, EV_KEYPRESS, M_KEYPRESS, on_key_press, game);
	mlx_hook(game->mlx.win, EV_KEYRELEASE, M_KEYRELEASE, on_key_release, game);
	mlx_hook(game->mlx.win, EV_DESTROY, 0, on_destroy, game);
	mlx_loop_hook(game->mlx.ptr, game_loop, game);
	setup_mouse_hook(game);
}

int	on_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (on_destroy(game));
	set_key_state(keycode, game, 1);
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	set_key_state(keycode, game, 0);
	return (0);
}
