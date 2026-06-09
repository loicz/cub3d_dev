/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:53:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/09 17:26:16 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}

void	draw_vertical_line(t_vec low, t_vec high, t_img img, int color)
{
	int i;
	int y;
	int x;
	int distance;

	i = 0;
	y = low.y;
	x = low.x;
	if(high.x != low.x)
		return ;
	distance = (int)fabs(low.y - high.y);
	while (i <= distance)
	{
		if (x >= 0 && x <= img.width && y >= 0 && y <= img.height)
			img.addr[get_index(x, y, img.line_len)] = color;
		y++; 
		i++;
	}
}

void	draw_window(t_game *game, int x, t_vec high_wall, t_vec low_wall)
{
	t_vec max_win;
	t_vec min_win;
	
	max_win.x = x;
	max_win.y = WIN_H;
	min_win.x = x;
	min_win.y = 0;

	if(high_wall.y >= 0 && high_wall.y <= WIN_H / 2)
		draw_vertical_line(min_win, high_wall, game->frame, game->config.ceil_color); //dessiner le ciel
	if(low_wall.y <= WIN_H && low_wall.y >= WIN_H / 2)
		draw_vertical_line(low_wall, max_win, game->frame, game->config.floor_color); //dessiner le sol
	draw_vertical_line(high_wall, low_wall, game->frame, 0xFFFF25FF); //dessiner le mur
}