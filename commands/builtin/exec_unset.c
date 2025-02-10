#include "./../../minishell.h"

void exec_unset(t_token *token, t_mini *mini)
{
	t_env	*ev;
	t_env *temp;
	t_token *next;

	next = token->next;
	ev = mini->envp;
	temp = NULL;
	while (ev)
	{
		if (ft_strcmp(ev->var, next->cmd) == 0)
		{
			temp = ev;
			if (ev->prev && ev->next)
			{                
				ev->prev->next = ev->next;
				ev->next->prev = ev->prev;
			}
			else if (!ev->prev)
			{
				ev->next->prev = NULL;
				ev = ev->next;
			}
			else if (!ev->next)
			{
				ev->prev->next = NULL;
			}
			free(temp);
			return ;
		}     
		ev = ev->next;
	}
}
