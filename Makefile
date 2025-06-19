NAME_MAN := pipex
DIR_INC := ./include

LIBFTNAME := libft.a
LIBFTDIR := ./libft

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -I$(DIR_INC)

SRC_MAN := main.c \
	parse.c \
	free.c

OBJ_MAN := $(SRC_MAN:.c=.o)

all: $(NAME_MAN)

$(NAME_MAN): $(OBJ_MAN) $(LIBFTDIR)/$(LIBFTNAME)
	@$(CC) $(CFLAGS) $(OBJ_MAN) $(LIBFTDIR)/$(LIBFTNAME) -o $(NAME_MAN)

$(LIBFTDIR)/$(LIBFTNAME):
	@make -C $(LIBFTDIR) CFLAGS="$(CFLAGS)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJ_MAN) $(OBJ_BONUS) $(LIBFTDIR)/$(LIBFTNAME)

fclean: clean
	@make clean
	@rm -f $(NAME_MAN) $(NAME_BONUS)

re: fclean all
