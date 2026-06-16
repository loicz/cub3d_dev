/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:53:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/17 00:24:02 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cub(t_game *game, int y, int x, int color)
{
	int		i;
	t_vec	max_win;
	t_vec	min_win;

	min_win.y = y * game->mini_map.width / minimap_W;
	max_win.y = (y + 1) * game->mini_map.width / minimap_W;
	i = 0;
	while (i < game->mini_map.width / minimap_W)
	{
		max_win.x = i + ((x * game->mini_map.width) / minimap_W);
		min_win.x = i + ((x * game->mini_map.width) / minimap_W);
		// printf("x:%f\n", x);
		// printf("x:%f\n", min_win.x);
		draw_vertical_line(game, min_win, max_win, color);
		i++;
		// printf("enter\n");
	}
	// printf("\n\n\n\n");
	// printf("game->mini_map.width/minimap_W:%d\n", game->mini_map.width
	// / minimap_W);
	// printf("i:%d\n", i);
}

void	draw_mini_map(t_game *game, t_minimap *m, int i)
{
	while (i < minimap_W)
	{
		if (m->mapY >= game->map.height
			|| m->mapX >= game->map.row_len[m->mapY])
			m->mapX = m->mapX;
		else if (m->mapX == (int)game->player.pos.x
			&& m->mapY == (int)game->player.pos.y)
			draw_cub(game, m->Ydraw, m->Xdraw, 0xFF0000);
		else if (game->map.grid[m->mapY][m->mapX] == '0')
			draw_cub(game, m->Ydraw, m->Xdraw, 0x000000);
		else if (game->map.grid[m->mapY][m->mapX] == '1')
			draw_cub(game, m->Ydraw, m->Xdraw, 0x0010FF);
		else if (game->map.grid[m->mapY][m->mapX] == '2'
			|| game->map.grid[m->mapY][m->mapX] == '3')
			draw_cub(game, m->Ydraw, m->Xdraw, 0x8A3A01);
		// printf("m->xdraw:%d\n", m->Xdraw);
		i++;
		m->Xdraw++;
		m->mapX++;
	}
}

void	mini_map(t_game *game, t_minimap m)
{
	int	startX;
	int	i;

	m.mapX = (int)game->player.pos.x - (int)(minimap_W / 2);
	m.mapY = (int)game->player.pos.y - (int)(minimap_W / 2);
	// printf("(int)(minimap_W / 2):%d\n", (int)(minimap_W / 2));
	startX = m.mapX;
	while (m.mapY - ((int)game->player.pos.y - (int)(minimap_W
				/ 2)) < minimap_W)
	{
		m.mapX = startX;
		i = 0;
		m.Ydraw = m.mapY - ((int)game->player.pos.y - (int)(minimap_W / 2));
		m.Xdraw = m.mapX - ((int)game->player.pos.x - (int)(minimap_W / 2));
		draw_mini_map(game, &m, i);
		m.mapY++;
	}
}
