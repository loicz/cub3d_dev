/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:09:47 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/05 16:43:30 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	remove_bsN(char **line)
// {
// 	int	i;
//
// 	i = ft_strlen(*line);
// 	if ((*line)[i - 1] == '\n')
// 		(*line)[i - 1] = '\0';
// }

static int	first_element(int *first, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == '\t' ||
		line[i] == '\r' || line[i] == ' '))
			i++;
		count++;
		if (!*first)
			*first = i;
		while (line[i] && line[i] != '\t' &&
		line[i] != '\r' && line[i] != ' ')
			i++;
	}
	if (count != 1)
		return (1);
	return (0);
}
static int	store_line(char *line, t_game *game, t_dir dir, char color_p)
{
	int	first;

	first = 0;
	if (first_element(&first, line))
		return (1);
	if (dir != UNSET)
		game->config.tex_path[dir] = line + first;
	else
		write_colors(line + first, color_p, game);
	return (0);
}

static int	read_config_info(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '\t' ||
	line[i] == '\r' || line[i] == ' '))
		i++;
	if (!line[i])
		return (0);
	if (!ft_strncmp(line, "NO ", 3) && line[3])
		return (store_line(line + 3, game, NORTH, '0'));
	if (!ft_strncmp(line, "SO ", 3) && line[3])
		return (store_line(line + 3, game, SOUTH, '0'));
	if (!ft_strncmp(line, "WE ", 3) && line[3])
		return (store_line(line + 3, game, WEST, '0'));
	if (!ft_strncmp(line, "EA ", 3) && line[3])
		return (store_line(line + 3, game, EAST, '0'));
	if (!ft_strncmp(line, "F ", 2) && line[2])
		return (store_line(line + 2, game, UNSET, 'F'));
	if (!ft_strncmp(line, "C ", 2) && line[2])
		return (store_line(line + 2, game, UNSET, 'C'));
	return (1);
}

static int	get_map_config(t_game *game, bool *map_start, char *line)
{
	if (*map_start || !*line)
		return (0);
	if (read_config_info(game, line))
		return (1);
}

int	read_scene(int fd, t_game *game, t_line *tmp_line)
{
	char	*line;
	bool	map_start;
	int		i;

	map_start = false;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = ft_strlen(line);
		if (line[i - 1] == '\n')
			line[i - 1] = '\0';
		if (get_map_config(game, &map_start, line))
			return (err_msg("bad format for map config"));
		if (get_map_content(tmp_line, map_start, line))
			return (1);
		free(line);
	}
	return (0);
}
