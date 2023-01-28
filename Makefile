NAME = pushswap.a

NAMELIBFT = libft/libft.a

LIBDIR = ./include/

CC = cc

CFLAGS = -Wall -Wextra -Werror -I $(LIBDIR)

SRC_C = src/fdf.c

SRC_C_BONUS = src/bonus.c

all: $(NAME)

$(NAME):
	make all -C ./libft
	$(CC) -g $(CFLAGS) $(SRC_C) $(NAMELIBFT) -o push_swap

bonus:
	make all -C ./libft
	$(CC) -g $(CFLAGS) $(SRC_C_BONUS) $(NAMELIBFT) -o checker

clean:
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm -rf push_swap
	rm -rf checker

re: fclean all
