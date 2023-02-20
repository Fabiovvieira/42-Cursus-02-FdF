NAME = fdf.a

NAMELIBFT = libft/libft.a

NAMEMLX = minilibx/libmlx.a

LIBDIR = ./include/

INC=/usr/include/

INCLIB=$(INC)/../lib

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(LIBDIR) -I$(INC) -O3 -g

LFLAGS = $(NAMELIBFT) $(NAMEMLX) -L$(INCLIB) -lXext -lX11 -lm -lbsd

SRCS = src/fdf.c \
		src/menu.c \
		src/keys.c \
		src/init_free.c \
		src/iso_eq_1.c \
		src/iso_eq_2.c \
		src/draw.c \
		src/parallel_eq.c \
		src/draw_utils.c \
		src/map.c \
		src/color.c \

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(NAMELIBFT) $(NAMEMLX)
	@$(CC) -o fdf $(OBJS) $(LFLAGS)
	@echo "Compiled $@"

$(NAMELIBFT):
	@make all -s -C ./libft
	@echo "Compiled $@"

$(NAMEMLX):
	@make all -s -C ./minilibx
	@echo "Compiled $@"

clean:
	@rm -rf $(OBJS)
	@make -s -C ./libft clean
	@make -s -C ./minilibx clean
	@echo "Remove objects files."

fclean: clean
	@make -s -C ./libft fclean
	@make -s -C ./minilibx clean
	@rm -rf fdf
	@echo "Remove static libraries and executables."

re: fclean all
