/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:27:04 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 19:50:58 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	err_msg(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	exit_cub3d(t_game *game)
{
	free_parser_data(game);
	exit(1);
}
