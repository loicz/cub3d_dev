/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:56:47 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/02 16:57:12 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	is_dotcub(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4));
}

int	parse_scene(char *path, t_game *game)
{
	int	fd;

	if (!is_dotcub(path))
		return (perror("Error\nBad map format\n"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpen failed\n"), 1);

}
