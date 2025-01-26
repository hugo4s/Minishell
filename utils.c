#include "minishell.h"

void	check_pipe(char *cmd, t_token **head)
{
	char	*input;

	input = NULL;
	if (!ft_strncmp(cmd, "|", 2))
	{
		input = readline("> ");
		if (input && !input[0])
		{
			input = free_ptr(input);
			return ;
		}
		parser(head, input);
		input = free_ptr(input);
	}
}

void	exit_handler(t_mini *ms, const char *msg, const int code)
{
	int	i;

	if (code && code != 127)
		ft_putstr_fd ("ERROR\n", 2);
	if (msg)
		ft_putendl_fd ((char *) msg, 2);
	if (!code && !msg)
		ft_putendl_fd ("Bye!", 1);
	ms -> input = free_ptr (ms -> input);
	ms -> prompt = free_ptr (ms -> prompt);
	ms -> token = free_token (ms -> token);
	ms -> envp = free_mat (ms -> envp);
	rl_clear_history ();
	unlink("__heredoc");
	i = 0;
	while (!close(i))
		i++;
	exit(code);
}

char	**ft_matdup(char **mat)
{
	char	**temp;
	size_t	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
		i++;
	temp = ft_calloc (i + 1, sizeof (char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		temp[i] = ft_strdup (mat[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

int	check_quotes(char c, int quotes)
{
	if (c == '\"')
	{
		if (!quotes)
			return (1);
		else if (quotes == 1)
			return (0);
	}
	else if (c == '\'')
	{
		if (!quotes)
			return (2);
		else if (quotes == 2)
			return (0);
	}
	return (quotes);
}