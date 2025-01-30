#include "./../../minishell.h"

void exec_env(t_token *token, t_mini *mini)
{
    int i;

	(void)token;

    i = 0;
    while (mini->envp[i])
    {
        ft_putendl_fd(mini->envp[i], STDOUT_FILENO);
        i++;
    }
}
// Destroy -u --unset Create VAR1=valor1 PATH=/custom/path ls