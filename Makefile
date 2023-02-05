NAME = fdf.a

NAMELIBFT = libft/libft.a

NAMEMLX = minilibx/libmlx.a

LIBDIR = ./include/

INC=/usr/include/

INCLIB=$(INC)/../lib

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(LIBDIR) -I$(INC) -O3 -g

LFLAGS = $(NAMELIBFT) $(NAMEMLX) -L$(INCLIB) -lXext -lX11 -lm -lbsd

SRCS = src/fdf.c

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

# bonus:
# 	make all -C ./libft
# 	$(CC) -g $(CFLAGS) $(SRC_C_BONUS) $(NAMELIBFT) -o checker

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
