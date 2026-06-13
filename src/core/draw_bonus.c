/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:53:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/13 15:40:42 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}

int	color_texture(t_img img, int x, int i, int distance)
{
	int		color;
	double	ratio;
	int		y;

	ratio = (double)i / (double)distance;
	y = ratio * img.height;
	color = img.addr[get_index(x, y, img.line_len)];
	return (color);
}
void	draw_vertical_line(t_game *game, t_vec low, t_vec high, int color)
{
	int	i;
	int	text;
	int	dist;
	int	y;

	if (high.x != low.x)
		return ;
	y = low.y;
	text = 0;
	if (color == -1)
		text = 1;
	i = 0;
	dist = (int)fabs(low.y - high.y);
	while (i <= dist)
	{
		if (text == 1)
			color = color_texture(game->mlx.tex[game->ray.tex], game->ray.texX,
					i, dist);
		if (low.x >= 0 && low.x < game->mlx.frame.width && y >= 0
			&& y < game->mlx.frame.height)
			game->mlx.frame.addr[get_index(low.x, y,
					game->mlx.frame.line_len)] = color;
		y++;
		i++;
	}
}
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
void	mini_map(t_game *game, t_minimap m, t_player play)
{
	int	startX;
	int	Ydraw;
	int	Xdraw;
	int	i;

	m.mapX = (int)play.pos.x - (int)(minimap_W / 2);
	m.mapY = (int)play.pos.y - (int)(minimap_W / 2);
	// printf("(int)(minimap_W / 2):%d\n", (int)(minimap_W / 2));
	startX = m.mapX;
	while (m.mapY - ((int)play.pos.y - (int)(minimap_W / 2)) < minimap_W)
	{
		m.mapX = startX;
		i = 0;
		Ydraw = m.mapY - ((int)play.pos.y - (int)(minimap_W / 2));
		Xdraw = m.mapX - ((int)play.pos.x - (int)(minimap_W / 2));
		while (i < minimap_W)
		{
			if (m.mapY >= game->map.height
				|| m.mapX >= game->map.row_len[m.mapY])
				m.mapX = m.mapX;
			else if (m.mapX == (int)play.pos.x && m.mapY == (int)play.pos.y)
				draw_cub(game, Ydraw, Xdraw, 0xFF0000);
			else if (game->map.grid[m.mapY][m.mapX] == '0')
				draw_cub(game, Ydraw, Xdraw, 0x000000);
			else if (game->map.grid[m.mapY][m.mapX] == '1')
				draw_cub(game, Ydraw, Xdraw, 0x0010FF);
			// printf("xdraw:%d\n", Xdraw);
			i++;
			Xdraw++;
			m.mapX++;
		}
		m.mapY++;
	}
}
void	draw_window(t_game *game, int x, t_vec high_wall, t_vec low_wall)
{
	t_vec	max_win;
	t_vec	min_win;

	max_win.x = x;
	max_win.y = WIN_H;
	min_win.x = x;
	min_win.y = 0;
	if (high_wall.y >= 0 && high_wall.y <= WIN_H / 2)
		draw_vertical_line(game, min_win, high_wall, game->config.ceil_color);
	// dessiner le ciel
	if (low_wall.y <= WIN_H && low_wall.y >= WIN_H / 2)
		draw_vertical_line(game, low_wall, max_win, game->config.floor_color);
	// dessiner le sol
	draw_vertical_line(game, high_wall, low_wall, -1);
	// dessiner le mur
}
