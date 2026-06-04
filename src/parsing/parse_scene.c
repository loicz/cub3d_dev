/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:56:47 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/04 18:33:51 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_dotcub(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

int	parse_scene(char *path, t_game *game)
{
	int		fd;
	int		ret;
	t_line	tmp_line;


	if (!is_dotcub(path))
		return (err_msg("scene file must end with .cub"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg("cannot open scene file"));
	ret = read_scene(fd, game, &tmp_line);
	close(fd);
	if (ret)
		return (err_msg("bad format of .cub file"));
	return (0);
}
