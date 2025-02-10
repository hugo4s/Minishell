#include "./../../minishell.h"

void exec_env(t_token *token, t_mini *mini)
{
    t_env   *ev;
    int     i;

    i = 0;
    ev = mini->envp;
	(void)token;
    while (ev)
    {
        printf("%s\n", ev->content);
        /* if (ft_strcmp(ev->var, "OLDPWD") == 0)
		{
			printf("%s\n", ev->content);
		}
		else if (ft_strcmp(ev->var, "PWD") == 0)
		{
			printf("%s\n", ev->content);
		}  */       
        ev = ev->next;
        i++;
    }
    printf("%i\n", i);
}
// Destroy -u --unset Create VAR1=valor1 PATH=/custom/path ls