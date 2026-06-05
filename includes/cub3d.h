/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:41:53 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/05 18:32:17 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

//FENETRE
// servir a : ouvrir la fenetre via mlx + engine
// (nombre de  colonnes de rayons lancees par frame)
# define WIN_W 1280
# define WIN_H 720
# define WIN_TITLE "cub3D"

//MOVEMENT
// servir a : module events
// senario : mettre a jour le player
// ces valeur seront modifies par evaluateurs au moment de correction
# define MOVE_SPEED 0.045
# define ROT_SPEED 0.035
// collision: la distance securise minimale entre le player et le mur
# define PLAYER_RADIUS 0.20
// longuer du plan camera(la plus part de gens 
// fait avec 0.66 pour evider l'effet Fisheye)
# define PLANE_LEN 0.66

//KEYCODES
// servir a : module events
// valeurs definies par protocol X11 sous Linux
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

//Event type/mask
//servir a : module events (ex: parametre de mlx_hook dans setup_hooks)
# define EV_KEYPRESS 2
# define EV_KEYRELEASE 3
# define EV_DESTROY 17
# define M_KEYPRESS 1L
# define M_KEYRELEASE 2L

//DATA TYPE

// un vecteur 2d (ex: coordonees)
typedef struct s_vec
{
	double			x;
	double			y;
}	t_vec;

//structure pour image rendering
//(tu peux modifier en stucture de donnees que tu preferes si tu veux)
typedef struct s_img
{
	void			*ptr;
	void			*img;
	void			*win;
	int			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}	t_img;

/* t_dir : enum des directions servant d'indice pour tex_path[4] et tex[4]
   langage commun aux trois modules : parser, mlx, engine
   ex : "NO" -> tex_path[NORTH] ; mur nord -> tex[NORTH] */
typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_dir;

//informations player
//dir : l'orientation de player
//plane : longueur du plan camera
typedef struct s_player
{
	t_vec			pos_maps;
	t_vec			pos_cub;
	t_vec			dir;
	t_vec			plane;
}	t_player;

//map
/* grid    : tableau de lignes, acces case par grid[y][x]
   row_len : longueur reelle de chaque ligne (a verifier avant acces)
   height  : nombre de lignes
   width   : longueur de la ligne la plus longue (borne max, pas par ligne) */
typedef struct s_map
{
	char			**grid;
	int				*row_len;
	int				height;
	int				width;
}	t_map;

//configuration pour .cub
//contenir 4 path de texture et le couleur du plafond et le sol
//has_floor et has_ceil pour differencier le couleur noir {0,0,0} et "non set""
typedef struct s_config
{
	char			*tex_path[4];
	int				floor_color;
	int				ceil_color;
	int				has_floor;
	int				has_ceil;
}	t_config;

//l'etat actuel de clavier
typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}	t_keys;

/* ceete stucture est le contexte central
   accede a tout le monde (player / map / frame / keys) */
typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			*frame;
	t_img			tex[4];
	t_config		config;
	t_map			map;
	t_player		player;
	t_keys			keys;
}	t_game;
# include "./engine.h"

#endif
