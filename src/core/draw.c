/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:53:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/08 15:09:56 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

/* void	draw_segment(t_vec point1, t_vec point2, t_img **img, int step)
{
	int		i;
	float	dx;
	float	dy;
	float	x;
	float	y;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	step = fmax(fabs(dx), fabs(dy));
	dx = dx / step;
	dy = dy / step;
	x = point1.x;
	y = point1.y;
	i = 0;
	while (i <= step)
	{
		if (x >= 0 && x <= (*img)->height && y >= 0 && y <= (*img)->width)
			(*img)->addr[get_index(x, y, (*img)->line_len)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
} */
int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}

void	draw_vertical_line(t_vec low, t_vec high, t_img img, int color)
{
	int i;
	int y;
	int x;

	i = 0;
	y = low.y;
	x = low.x;
	if(high.x != low.x)
		return ;
	while (i <= high.y - low.y)
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