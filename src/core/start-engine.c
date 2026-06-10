/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/10 00:39:24 by lozhao           ###   ########.fr       */
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
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->mlx.frame.img,
	0, 0);
}

int	init_mlx(t_game *game)
{
	t_mlx	*mlx;
 
	mlx = &game->mlx;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (err_msg("mlx: init failed"));
	mlx->win = mlx_new_window(mlx->ptr, WIN_W, WIN_H, WIN_TITLE);
	if (!mlx->win)
		return (err_msg("mlx: window creation failed"));
	mlx->frame.width = WIN_W;
	mlx->frame.height = WIN_H;
	mlx->frame.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	if (!mlx->frame.img)
		return (err_msg("mlx: image creation failed"));
	mlx->frame.addr = (int *)mlx_get_data_addr(mlx->frame.img,
			&mlx->frame.bpp, &mlx->frame.line_len, &mlx->frame.endian);
	mlx->frame.line_len /= 4;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
 
	if (ac != 2)
		return (err_msg("usage: ./cub3D <map.cub>"));
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(av[1], &game))
		return (1);
	if (init_mlx(&game))
	{
		destroy_mlx(&game);
		free_parser_data(&game);
		return (1);
	}
	setup_hooks(&game); //je vais creer
	start_engine(&game);
	mlx_loop(game.mlx.ptr);
	destroy_mlx(&game);
	free_parser_data(&game);
	return (0);
}
