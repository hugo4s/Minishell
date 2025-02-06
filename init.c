#include "minishell.h"

t_mini init(char **envp)
{
    t_mini ms;

    ms.input = NULL;
    ms.envp = envp;
    ms.token = NULL;
    ms.prompt = "minishell$ ";
	ms.exit_status = 0;
	ms.in_quotes = 0;
    return ms;
}
