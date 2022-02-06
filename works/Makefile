NAME = pipex
NAME_BONUS = pipex_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
XSYSCALL_SRCS = $(addprefix srcs/xsyscall/, \
		xclose.c xfork.c xopen.c xpipe.c xwaitpid.c xdup2.c \
		)
XLIBFT_SRCS = $(addprefix srcs/xlibft/, \
		ft_xcalloc.c ft_xsplit.c ft_xstrdup.c ft_xstrjoin.c \
		)
SHARED_SRCS = $(addprefix srcs/shared/, \
		exec_pipex.c get_fullpath.c \
		)
PIPEX_SRCS = $(addprefix srcs/pipex/, \
		parser.c validate.c \
		)
PIPEX_BONUS_SRCS = $(addprefix srcs/pipex_bonus/, \
		 parser.c validate.c \
		)
SRCS = main.c $(PIPEX_SRCS) $(SHARED_SRCS) $(XLIBFT_SRCS) $(XSYSCALL_SRCS)
OBJS = $(SRCS:%.c=%.o)
SRCS_BONUS = main_bonus.c $(PIPEX_BONUS_SRCS) $(SHARED_SRCS) $(XLIBFT_SRCS) $(XSYSCALL_SRCS)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)
LIBS = -lft -Llibft
INCS = -Ilibft/includes -Iincludes

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

all: $(NAME)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

re: fclean all

.PHONY: all fclean clean re bonus test

# DELETE #
# BELOW IS ONLY FOR DEVELOPING PURPOSE #
.PHONY: test
test:
	make -C ../tests
