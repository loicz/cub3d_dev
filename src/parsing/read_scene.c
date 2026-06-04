/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:09:47 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/05 00:45:08 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static void	remove_bsN(char **line)
{
	int	i;

	i = ft_strlen(*line);
	(*line)[i - 1] = '\0';
}

static int	get_map_config(t_game *game, bool map_start, char *line)
{
	if (map_start)
		return (0);
	if (ft_strncmp(line, "NO ", 3) && line[3])
	{
		game->config.tex_path[NORTH] = line + 3;
		return (0);
	}
	if (ft_strncmp(line, "SO ", 3) && line[3])
	{
		game->config.tex_path[SOUTH] = line + 3;
		return (0);
	}
	if (ft_strncmp(line, "WE ", 3) && line[3])
	{
		game->config.tex_path[WEST] = line + 3;
		return (0);
	}
	if (ft_strncmp(line, "EA ", 3) && line[3])
	{
		game->config.tex_path[EAST] = line + 3;
		return (0);
	}
	return (1);
}

int	read_scene(int fd, t_game *game, t_line *tmp_line)
{
	char	*line;
	bool	map_start;

	map_start = false;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		remove_bsN(&line);
		if (get_map_config(game, map_start, line))
			return (err_msg("bad format for map config"));
		if (get_map_content(tmp_line, map_start, line))
			return (1);
		free(line);
	}
	return (0);
}
