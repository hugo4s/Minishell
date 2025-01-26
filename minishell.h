#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./42-libft/libft.h"

typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**envp;
	t_token	*token;
	char	error;
	char	exit;
}	t_mini;

enum e_type{
	PIPE = 10,
	EXECVE = 11,
	BUILDIN = 12,
	ARG = 13,
	ARG_FILE = 14,
	REDIRECT = 15,
	HEREDOC = 16
};

// open()
// O_APPEND
// O_CREAT
// O_EXCL
// O_RDONLY
// O_TRUNC
// O_WRONLY
# include <fcntl.h>

// add_history()
# include <readline/history.h>

// readline()
// rl_clear_history() 
// rl_on_new_line()
// rl_redisplay()
// rl_replace_line()
# include <readline/readline.h>

// sigaction()
# include <signal.h>

// perror()
# include <stdio.h>

// exit()
// free()
# include <stdlib.h>

// waitpid()
// WEXITSTATUS()
// WIFEXITED()
# include <sys/wait.h>

// chdir()
// close()
// dup2()
// execve()
// fork()
// getcwd()
// pipe()
// unlink()
// write()
# include <unistd.h>

# include "./42-libft/libft.h"

char	**lexer(char *input);
int	parser(t_token **head, char *str);
void	exit_handler(t_mini *ms, const char *msg, const int code);

char	*free_ptr(char *ptr);
char	**free_mat(char **mat);
t_token	*free_token(t_token *token);
char	**ft_matdup(char **mat);

int	syntax_checker(t_mini *ms);

void	check_pipe(char *cmd, t_token **head);
int	check_quotes(char c, int quotes);

#endif