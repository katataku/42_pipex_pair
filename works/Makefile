NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c
OBJS = $(SRCS:%.c=%.o)
SRCS_BONUS =
OBJS_BONUS =
LIBS = -lft -Llibft
INCS = -Ilibft -Iincludes

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBS) $(OBJS_BONUS) -o $(NAME_BONUS)

test:
	make -C ../google_tests

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

all: $(NAME)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

re: fclean all

.PHONY: all fclean clean re bonus test
