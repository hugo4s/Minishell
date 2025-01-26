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
}	t_mini;

typedef enum e_cmd_type {
    CMD_NONE = 0,
    CMD_PIPE = 10,
    CMD_EXEC = 11,
    CMD_BUILDIN = 12,
    CMD_ARG = 13,
    CMD_ARG_FILE = 14,
    CMD_REDIRECT = 15,
    CMD_HEREDOC = 16
} t_cmd_type;

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

t_mini init(char **envp);
char *get_input(t_mini *ms, char *prompt);
t_token *lexer(char *input);
void parser(t_mini *ms);

#endif