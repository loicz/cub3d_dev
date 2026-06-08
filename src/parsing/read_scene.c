/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:09:47 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 00:05:00 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	strip_line_end(char *line)
{
	int	i;

	i = ft_strlen(line);
	if (i > 0 && line[i - 1] == '\n')
		line[--i] = '\0';
	if (i > 0 && line[i - 1] == '\r')
		line[i - 1] = '\0';
}

static int	scene_error(char *line, t_line *tmp)
{
	if (line)
		free(line);
	free_tmp_lines(tmp);
	return (1);
}

int	read_scene(int fd, t_game *game, t_line *tmp_line)
{
	char	*line;
	bool	map_start;

	map_start = false;
	line = get_next_line(fd);
	while (line)
	{
		strip_line_end(line);
		if (get_map_config(game, &map_start, line))
			return (scene_error(line, tmp_line));
		if (get_map_content(tmp_line, map_start, line))
			return (scene_error(line, tmp_line));
		free(line);
		line = get_next_line(fd);
	}
	if (!map_start || build_map(game, tmp_line))
		return (scene_error(NULL, tmp_line));
	return (0);
}
