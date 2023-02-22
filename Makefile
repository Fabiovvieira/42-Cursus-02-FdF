NAME = fdf.a

NAMELIBFT = libft/libft.a

NAMEMLX = minilibx/libmlx.a

LIBDIR = ./include/

INC=/usr/include/

INCLIB=$(INC)/../lib

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INC) -I$(LIBDIR) -O3 -g

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

SRCS_B = src_bonus/fdf_bonus.c \
		src_bonus/menu_bonus.c \
		src_bonus/keys_bonus.c \
		src_bonus/init_free_bonus.c \
		src_bonus/iso_eq_1_bonus.c \
		src_bonus/iso_eq_2_bonus.c \
		src_bonus/draw_bonus.c \
		src_bonus/parallel_eq_bonus.c \
		src_bonus/draw_utils_bonus.c \
		src_bonus/map_bonus.c \
		src_bonus/color_bonus.c \

OBJS_B = $(SRCS_B:%.c=%.o)

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

bonus: $(OBJS_B) $(NAMELIBFT) $(NAMEMLX)
	@$(CC) -o fdf_bonus $(OBJS_B) $(LFLAGS)
	@echo "Compiled $@"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJS_B)
	@make -s -C ./libft clean
	@make -s -C ./minilibx clean
	@echo "Remove objects files."

fclean: clean
	@make -s -C ./libft fclean
	@make -s -C ./minilibx clean
	@rm -rf fdf
	@rm -rf fdf_bonus
	@echo "Remove static libraries and executables."

re: fclean all
