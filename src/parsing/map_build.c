/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:57:16 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 01:59:47 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	alloc_map(t_game *game, t_line *tmp)
{
	game->map.grid = malloc(sizeof(char *) * (tmp->size + 1));
	game->map.row_len = malloc(sizeof(int) * tmp->size);
	if (!game->map.grid || !game->map.row_len)
	{
		free(game->map.grid);
		free(game->map.row_len);
		game->map.grid = NULL;
		game->map.row_len = NULL;
		return (1);
	}
	game->map.height = tmp->size;
	game->map.width = 0;
	return (0);
}

int	build_map(t_game *game, t_line *tmp)
{
	int	i;
	int	len;

	if (tmp->size == 0)
		return (1);
	if (alloc_map(game, tmp))
		return (1);
	i = 0;
	while (i < tmp->size)
	{
		game->map.grid[i] = tmp->data[i];
		tmp->data[i] = NULL;
		len = ft_strlen(game->map.grid[i]);
		game->map.row_len[i] = len;
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
	game->map.grid[i] = NULL;
	free(tmp->data);
	tmp->data = NULL;
	tmp->size = 0;
	tmp->capacity = 0;
	return (validate_map(game));
}
