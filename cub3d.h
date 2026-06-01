/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:41:53 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/01 14:42:06 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** 提交前：上面 42 header 用编辑器插件重生成(Neovim :Stdheader)，
** 换成你自己的 login/邮箱/时间戳并保证对齐。本文件注释偏多，是给
** 队友看的"导览版"；若想精简提交版，可删掉中文说明，结构不要动。
*/

#ifndef CUB3D_H
# define CUB3D_H

/* ====================== includes ============================= */
/* 谁需要谁: 解析需 open/read/close; 渲染需 MLX; 引擎需 math */
# include <stdlib.h>     /* malloc free exit          —— 各模块  */
# include <unistd.h>     /* read write close          —— parser  */
# include <fcntl.h>      /* open                      —— parser  */
# include <stdio.h>      /* perror                    —— 错误处理 */
# include <string.h>     /* strerror                  —— 错误处理 */
# include <math.h>       /* sin cos fabs floor (-lm)  —— 引擎    */
# include <sys/time.h>   /* gettimeofday              —— bonus 动画*/
# include "mlx.h"        /* MinilibX                  —— mlx/事件 */
# include "libft.h"      /* libft (Makefile -Ilibft)  —— 各模块  */
/* 若用 MLX 源码版而非系统版，在 Makefile 的 INCLUDES 里加 mlx 目录 */

/* ====================== window ============================== */
/* 服务: mlx 开窗 + 引擎(决定一帧有多少列光线) */
/* 场景: init_mlx_game 用 WIN_W/WIN_H 开窗; raycast 循环 x:0..WIN_W */
# define WIN_W 1280
# define WIN_H 720
# define WIN_TITLE "cub3D"

/* ====================== movement =========================== */
/* 服务: events 模块。场景: update_player 每帧用这些步长改 player */
/* 答辩可现场改这些值 → 故集中定义 */
# define MOVE_SPEED 0.045
# define ROT_SPEED 0.035
# define PLAYER_RADIUS 0.20      /* 碰撞: 玩家离墙的安全半径 */
# define PLANE_LEN 0.66          /* 相机平面长度=半 FOV; 0.66≈66度 */

/* ================= keycodes (Linux X11) ==================== */
/* 服务: events 模块。场景: on_key_press 里 switch(keycode) 比对 */
/* 注意: 42 Paris Linux keysym; macOS 不同 */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* ========== X11 事件类型/掩码 (自定义名防与 X11 头冲突) ====== */
/* 服务: events 模块。场景: setup_hooks 里 mlx_hook 的参数 */
/* mlx.h 会间接定义 X11 的 KeyPress 等同名宏，故这里改前缀 EV_/M_ */
# define EV_KEYPRESS 2
# define EV_KEYRELEASE 3
# define EV_DESTROY 17
# define M_KEYPRESS 1L
# define M_KEYRELEASE 2L
# define M_STRUCTURE (1L << 17)

/* ======================= types ============================= */

/*
** t_vec —— 二维向量(几何原子)
** 服务模块 : 引擎(raycast) + events(移动/转向)
** 服务对象 : player.pos/dir/plane、每条光线的方向，本质都是它
** 场景举例 : rotate_player 对 dir 和 plane 各做一次旋转矩阵;
**            前进 = pos.x += dir.x * MOVE_SPEED
** 为何 double: 玩家站在格子内任意点(如 2.5,3.7)，整数会丢精度
*/
typedef struct s_vec
{
	double			x;
	double			y;
}	t_vec;

/*
** t_img —— 一张 MLX 图像(此结构是 MLX 接口的镜像)
** 服务模块 : mlx(创建) + render(写 frame) + 引擎(读 tex)
** 服务对象 : frame=渲染目标(往里写); tex[4]=纹理源(从里读)
** 场景举例 : put_pixel 往 frame.addr 写一个像素;
**            get_tex_pixel 从 tex[dir].addr 读墙的某点颜色
** 字段来源 : addr/bpp/line_len/endian 来自 mlx_get_data_addr;
**            width/height 自存，采样纹理时当边界
*/
typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}	t_img;

/*
** t_dir —— 方向枚举(钉成数组下标，是三方共用的"方向语言")
** 服务模块 : parser(填路径) + mlx(载图) + 引擎(取墙纹理)
** 服务对象 : config.tex_path[4] 和 game.tex[4] 的索引
** 场景举例 : parser 识别 "NO" -> tex_path[NORTH]=路径;
**            raycast 算出撞的是北面 -> 用 tex[NORTH] 画;
**            load_textures 用 for(d=0;d<4;d++) 一循环载完
*/
typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_dir;

/*
** t_player —— 玩家(本质是一台相机的数学模型)
** 服务模块 : 引擎(读它当相机) + events(每帧改它)
** 服务对象 : raycast 每列用 dir+plane*camera_x 算光线方向
** 场景举例 : init_ray 读 pos/dir/plane; update_player 改 pos;
**            转视角时 rotate_player 同时转 dir 和 plane
** 为何存向量不存角度: 渲染热循环里不必反复算 sin/cos
*/
typedef struct s_player
{
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
}	t_player;

/*
** t_map —— 地图网格
** 服务模块 : parser(产出) -> 引擎(DDA/碰撞读) + bonus(minimap读)
** 服务对象 : grid 给 DDA 查墙; row_len 给 map_get 判越界
** 场景举例 : perform_dda 里 is_blocking_cell 查 grid[y][x]=='1';
**            map_get(x,y) 对越界或短行尾返回 ' '(地图外)
** 关键设计 : cub3D 地图可不等宽 -> 必须存每行真实长度 row_len;
**            grid 保留原始字符(不转 int)，方便 bonus 加 D/2
*/
typedef struct s_map
{
	char			**grid;
	int				*row_len;
	int				height;
	int				width;
}	t_map;

/*
** t_config —— .cub 配置(纹理路径 + 两种颜色)
** 服务模块 : parser(产出) -> mlx(读 tex_path 载图) + render(读 F/C)
** 服务对象 : load_textures 读 tex_path; draw_background 读颜色
** 场景举例 : parser 读到 "F 220,100,0" -> floor_color=打包值,
**            has_floor=1; load_textures 用 tex_path[NORTH] 载北墙图
** 关键设计 : has_floor/has_ceil 区分"设了黑色(0,0,0)"与"忘了写",
**            不要拿数值 0 当"未设置"的哨兵
*/
typedef struct s_config
{
	char			*tex_path[4];
	int				floor_color;
	int				ceil_color;
	int				has_floor;
	int				has_ceil;
}	t_config;

/*
** t_keys —— 当前被按住的按键快照
** 服务模块 : events(写) -> update_player(读)
** 服务对象 : on_key_press/release 写标志; on_loop 每帧读标志移动
** 场景举例 : 按 W -> keys.w=1; 松 W -> keys.w=0;
**            update_player: if (keys.w) 前进, if (keys.left) 左转
** 为何用状态而非按一下走一步: 移动平滑、速度恒定、支持多键同按
*/
typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}	t_keys;

/*
** t_ray —— 单列光线的临时计算量
** 服务模块 : 引擎(raycast)内部
** 服务对象 : 不进 t_game! 在 raycast_walls 里逐列声明在栈上
** 场景举例 : for(x=0;x<WIN_W;x++){ t_ray r; init_ray(&r,x);
**            perform_dda(&r); compute_wall_slice(&r); 画第 x 列 }
** 为何不进 t_game: 它是"用完即弃"的中间结果，不是世界状态
*/
typedef struct s_ray
{
	t_vec			dir;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_dist;
	int				step_x;
	int				step_y;
	int				side;
	int				tex_x;
	int				line_h;
	int				draw_start;
	int				draw_end;
}	t_ray;

/*
** t_game —— 中央上下文(整个程序的"世界状态")
** 服务模块 : 全体。所有模块只通过它读写、互相沟通
** 服务对象 : MLX hook 的 void* 参数就是 &game，于是每个回调都能
**            拿到整个世界(player/map/frame/keys 全在手边)
** 场景举例 : mlx_hook(win, EV_KEYPRESS, M_KEYPRESS, on_key_press, &g);
**            on_loop(&g){ update_player(&g); render_frame(&g); }
** 内存说明 : 仅 mlx/win 是 MLX 句柄指针; 其余子结构按值内嵌,
**            随 t_game 一起释放; 真正在堆上的是 map.grid/row_len、
**            config.tex_path[] 字符串、以及 MLX 图像
*/
typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_img			tex[4];
	t_config		config;
	t_map			map;
	t_player		player;
	t_keys			keys;
}	t_game;

/* ===================== prototypes ========================== */

/* ---- core: 生命周期 + 错误(所有错误 ->stderr) ---- */
void	init_empty_game(t_game *g);
void	free_game(t_game *g);
void	error_exit(t_game *g, char *msg);
int		close_game(t_game *g);

/* ---- parsing: .cub -> config/map/player (你负责) ---- */
void	parse_scene(char *path, t_game *g);
void	parse_element(char *line, t_game *g);
void	parse_color(char *line, int *color, int *has_flag);
void	parse_texture(char *line, char **slot);
void	parse_map(char **lines, int start, t_game *g);
void	validate_config(t_game *g);
void	validate_map(t_game *g);
char	map_get(t_map *map, int x, int y);
int		parse_u8_component(char **s, int *out);

/* ---- mlx: 开窗/载纹理/销毁 ---- */
void	init_mlx_game(t_game *g);
void	load_textures(t_game *g);
void	destroy_mlx(t_game *g);

/* ---- raycast: 算每列墙 ---- */
void	raycast_walls(t_game *g);
void	init_ray(t_game *g, t_ray *r, int screen_x);
void	perform_dda(t_game *g, t_ray *r);
void	compute_wall_slice(t_game *g, t_ray *r);
int		is_blocking_cell(t_game *g, int x, int y);

/* ---- render: 写像素到 frame ---- */
void	render_frame(t_game *g);
void	draw_background(t_game *g);
void	draw_wall_column(t_game *g, t_ray *r, int x);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_tex_pixel(t_img *tex, int x, int y);

/* ---- events: 输入 + 每帧更新 ---- */
void	setup_hooks(t_game *g);
int		on_key_press(int keycode, t_game *g);
int		on_key_release(int keycode, t_game *g);
int		on_loop(t_game *g);
void	update_player(t_game *g);
void	apply_move(t_game *g, double dx, double dy);
void	rotate_player(t_game *g, double angle);

/* ---- utils ---- */
int		rgb_to_int(int r, int g, int b);

#endif
