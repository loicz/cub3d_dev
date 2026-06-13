#### VARIABLES ####
NAME = cub3D
TEST = parser_test
LIBFT = ./libft/libft.a
MLX = ./minilibx-linux/libmlx.a



VAL = valgrind
LEAKS = -s --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes
HEADER_PATH = includes
SUPP = --suppressions=mlx.supp
CC= cc
INC = -I $(HEADER_PATH) -I ./libft -I ./minilibx-linux -IGNL
# OBJ=ft_*.c =.o
# SRCS = $(HEADER_PATH)ft_atoi
D_ENGINE = ./src/core/
D_PARSE = ./src/parsing/
D_UTILS = ./src/utils/
D_GNL = ./GNL/
D_TEST = ./tests/
D_EVENTS = ./src/events/
D_BONUS = ./src_bonus/

#### SOURCE ####
ENGINE_FILES = $(D_ENGINE)start-engine.c \
		$(D_ENGINE)draw.c \
		$(D_ENGINE)ray.c \

BONUS_ENGINE_FILES = $(D_ENGINE)start-engine_bonus.c \
		$(D_ENGINE)draw_bonus.c \
		$(D_ENGINE)ray.c \

PARSER_FILES =	$(D_PARSE)parse_scene.c \
				$(D_PARSE)read_scene.c \
				$(D_PARSE)get_config.c \
				$(D_PARSE)get_config_store.c \
				$(D_PARSE)get_config_utils.c \
				$(D_PARSE)map_lines.c \
				$(D_PARSE)map_build.c \
				$(D_PARSE)map_check.c \
				$(D_PARSE)map_check_utils.c \
				$(D_PARSE)parser_free.c \
				$(D_GNL)get_next_line.c \
				$(D_UTILS)utils.c \
				$(D_GNL)get_next_line_utils.c

EVENT_FILES =	$(D_EVENTS)hooks.c \
				$(D_EVENTS)update.c \
				$(D_EVENTS)move.c \
				$(D_EVENTS)rotate.c \
				$(D_EVENTS)expose.c

BONUS_EVENT_FILES =	$(D_BONUS)hooks_bonus.c \
					$(D_EVENTS)update.c \
					$(D_EVENTS)move.c \
					$(D_EVENTS)rotate.c \
					$(D_EVENTS)expose.c \
					$(D_BONUS)mouse_bonus.c

SRC_FILES = $(ENGINE_FILES) $(PARSER_FILES) $(EVENT_FILES)
BONUS_SRC_FILES = $(BONUS_ENGINE_FILES) $(PARSER_FILES) $(BONUS_EVENT_FILES)

TEST_FILES = $(D_TEST)test_parser.c $(PARSER_FILES)

OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_SRC_FILES:.c=.o)
TEST_OBJ = $(TEST_FILES:.c=.o)
# SUPP = --suppressions=$(PWD)/readline.supp
# HEADER_PATH = include
CC= cc
# CFLAGS=-Wall -Wextra -Werror -I $(HEADER0_PATH)
CFLAGS=-Wall -Wextra -Werror -g3 -std=gnu99
# OBJ=ft_*.c =.o
# SRCS = $(HEADER_PATH)ft_atoi

#### SOURCE ####
OBJ_FILES = $(SRC_FILES:.c=.o)

#### RULES ####
all: ${NAME} PRINT


${NAME} : ${LIBFT} ${MLX} ${OBJ_FILES}
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -L./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

$(TEST) : $(LIBFT) $(TEST_OBJ)
	@$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBFT) -o $(TEST)

%.o: %.c
	@${CC} ${CFLAGS} $(INC) -c $< -o $@

${LIBFT} :
	@$(MAKE) -C ./libft

${MLX} :
	@$(MAKE) -C ./minilibx-linux

good: re clean

bonus: $(LIBFT) $(MLX) $(BONUS_OBJ_FILES)
	@$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT) -L./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(NAME) bonus ✅"

clean:
	@rm -f ${OBJ_FILES} ${BONUS_OBJ_FILES} ${TEST_OBJ}
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./minilibx-linux clean

fclean: clean
	@rm -f ${NAME} ${TEST} .bonus
	@$(MAKE) -C ./libft fclean

re: fclean all

val : ${NAME}
	@$(VAL) $(LEAKS) $(SUPP) ./$(NAME) ./maps/basic.cub

parser: $(TEST)
	@echo "$(TEST) ✅"

PRINT :
	@echo $(NAME) ✅

.PHONY: all clean fclean re good val parser val-parser PRINT bonus
