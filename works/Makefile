NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
XSYSCALL_SRCS = $(addprefix srcs/xsyscall/, \
		xclose.c xfork.c xopen.c xpipe.c xwaitpid.c xdup2.c \
		)
PIPEX_SRCS = $(addprefix srcs/, \
	pipex.c get_fullpath.c ft_xutils.c \
	)
SRCS = main.c $(PIPEX_SRCS) $(XSYSCALL_SRCS) 
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
