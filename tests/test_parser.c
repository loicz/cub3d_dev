/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 20:36:48 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 02:57:05 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Usage: ./parser_test <map.cub>\n", 31);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(argv[1], &game))
		return (1);
	write(1, "Parser OK\n", 10);
	free_parser_data(&game);
	return (0);
}
