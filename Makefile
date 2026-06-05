#### VARIABLES ####
NAME = cub3d
LIBFT = ./libft/libft.a
MLX = ./minilibx-linux/libmlx.a



VAL = valgrind
LEAKS = -s --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes
# SUPP = --suppressions=$(PWD)/readline.supp
# HEADER_PATH = include
CC= cc
# CFLAGS=-Wall -Wextra -Werror -I $(HEADER0_PATH)
CFLAGS=-Wall -Wextra -Werror
# OBJ=ft_*.c =.o
# SRCS = $(HEADER_PATH)ft_atoi
D_ENGINE = ./src/core/

#### SOURCE ####
SRC_FILES = $(D_ENGINE)start-engine.c \
		$(D_ENGINE)draw.c
OBJ_FILES = $(SRC_FILES:.c=.o)
# OBJ_FILES = $(addsuffix .o, $(SRC_FILES))
#### RULES ####
all: ${NAME} PRINT


${NAME} : ${LIBFT} ${MLX} ${OBJ_FILES} 
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -L./minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@ -g3

${LIBFT} :
	@$(MAKE) -C ./libft

${MLX} :
	@$(MAKE) -C ./minilibx-linux 

good: re clean

clean:
	@rm -f ${OBJ_FILES}
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f ${NAME}
	@$(MAKE) -C ./libft fclean

re: fclean  all

val :
	@$(VAL) $(LEAKS) ./$(NAME)
PRINT :
	@echo $(NAME) ✅

.PHONY: all clean fclean re good val PRINT
