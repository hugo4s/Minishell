CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./42-libft
LIBS = -lreadline -L./42-libft -lft
SRCS = main.c init.c lexer.c input.c parser.c valid_syntax.c executable.c \
       ./commands/exec_heredoc.c ./commands/exec_pipe.c \
       ./commands/exec_redirect.c ./commands/exec_command.c ./commands/exec_builtin.c \
       ./commands/builtin/exec_cd.c ./commands/builtin/exec_echo.c \
       ./commands/builtin/exec_exit.c ./commands/builtin/exec_env.c \
       ./commands/builtin/exec_export.c ./commands/builtin/exec_pwd.c \
       ./commands/builtin/exec_unset.c ./commands/executable/exec_cat.c \
	   ./commands/executable/exec_clear.c ./commands/executable/exec_cp.c \
	   ./commands/executable/exec_grep.c ./commands/executable/exec_head.c \
	   ./commands/executable/exec_ls.c ./commands/executable/exec_mkdir.c \
	   ./commands/executable/exec_mv.c ./commands/executable/exec_ps.c \
	   ./commands/executable/exec_rm.c ./commands/executable/exec_sort.c \
	   ./commands/executable/exec_tail.c ./commands/executable/exec_touch.c \
	   ./commands/executable/exec_wc.c handle_token.c \

OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./42-libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C ./42-libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./42-libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
