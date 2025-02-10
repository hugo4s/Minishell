#include "./../../minishell.h"

void	expand_var(char *var, t_mini *mini);

void exec_echo(t_token *token, t_mini *mini)
{
	t_token	*next;
	int		i;

	next = token->next;
	if (!next)
		printf("\n");	
	else if (next->cmd[0] == '$')
		expand_var(&next->cmd[1], mini);
	else
	{
		if (next->cmd[0] == '\"')
			next->cmd++;	
		while (next)
		{
			if (next->next)
				printf("%s ", next->cmd);
			else
			{
				i = ft_strlen(next->cmd);
				if (next->cmd[--i] == '\"')
					next->cmd[i] = '\0';
				printf("%s", next->cmd);
			}
			next = next->next;
		}
		printf("\n");
	}
}


void	expand_var(char *var, t_mini *mini)
{
	int		i;
	char	*content;

	i = ft_strlen(var);
	content = get_var_content(var, i + 1, mini->envp);
	if (!content)
		printf("\n");
	else
		printf("%s\n", content);
	if (content)
		free(content);
}

