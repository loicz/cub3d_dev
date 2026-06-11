/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 01:01:38 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/11 01:08:43 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_expose(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win,
		game->mlx.frame.img, 0, 0);
	return (0);
}
