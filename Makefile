CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./42-libft
LIBS = -lreadline -L./42-libft -lft
SRCS = main.c init.c lexer.c input.c parser.c
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