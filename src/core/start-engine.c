/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/04 15:19:04 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double launch_ray(int nb, )
{

}
void	draw_segment(t_point point1, t_point point2, t_img **img, int step)
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
		if (x >= 0 && x <= (*img)->length && y >= 0 && y <= (*img)->width)
			(*img)->buffer_img[get_index(x, y, (*img)->size_line)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
}
start_engine()
{
	int i;
	double dist_ray;
	
	i = 0;
	while(i < WIN_W)
	{
		dist_ray=launch_ray(i, )

		draw_segment();
		i++;
	}
}
