/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/11 12:16:56 by tle-rhun         ###   ########.fr       */
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
		dist_ray = launch_ray(i, game, &game->ray);
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
int	load_texture(t_game *game, t_img *tex, int i)
{
	tex->img = mlx_xpm_file_to_image(game->mlx.ptr, game->config.tex_path[i],
			&game->mlx.tex[i].width, &game->mlx.tex[i].height);
	if (!tex->img)
		return (err_msg("texture load failed, expected a valid XPM file"));
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (err_msg("texture load failed, expected a valid XPM file"));
	tex->line_len /= 4;
	return (0);
}
int	init_mlx(t_game *game)
{
	t_mlx	*mlx;
	int		i;

	i = 0;
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
	mlx->frame.addr = (int *)mlx_get_data_addr(mlx->frame.img, &mlx->frame.bpp,
			&mlx->frame.line_len, &mlx->frame.endian);
	mlx->frame.line_len /= 4;
	while (i < 2)
	{
		// printf("path texture:%s\n", game->config.tex_path[i]);
		load_texture(game, &game->mlx.tex[i], i);
		i++;
	}
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
	setup_hooks(&game);
	start_engine(&game);
	// mlx_put_image_to_window(game.mlx.ptr, game.mlx.win, game.mlx.tex[0].img,
	// 200, 0);
	mlx_loop(game.mlx.ptr);
	destroy_mlx(&game);
	free_parser_data(&game);
	return (0);
}
