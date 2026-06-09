/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/09 17:23:34 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



void	start_engine(t_game *game)
{
	int		i;
	double	dist_ray;
	t_vec	high_wall;
	t_vec	low_wall;

	i = 0;
	while (i < WIN_W)
	{
		dist_ray=launch_ray(i, game, game->ray);
		high_wall.x = i;
		high_wall.y = WIN_H / 2 - ((1 / dist_ray * WIN_H) / 2);
		low_wall.x = i;
		low_wall.y = WIN_H / 2 + ((1 / dist_ray * WIN_H / 2));
		draw_window(game, i, high_wall, low_wall);
		i++;
	}
	mlx_put_image_to_window(game->frame.ptr, game->frame.win, game->frame.img,
	0, 0);
}

void	initialise_mlx(t_img *img)
{
	img->height = WIN_H;
	img->width = WIN_W;
	img->ptr = mlx_init();
	img->win = mlx_new_window(img->ptr, img->width, img->height, WIN_TITLE);
	img->img = mlx_new_image(img->ptr, img->width, img->height);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->line_len /= 4;
}

int	main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
	{
		write(2, "Usage: ./parser_test <map.cub>\n", 31);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(av[1], &game))
		return (1);
	initialise_mlx(&game.frame);
	start_engine(&game);
	
	mlx_loop(game.frame.ptr);
	// free_parser_data(&game);
	return (0);
}
