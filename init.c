#include "minishell.h"

t_mini init(char **envp)
{
    t_mini ms;

    ms.input = NULL;
    ms.envp = envp;
    ms.token = NULL;
    ms.prompt = "minishell$ ";
    return ms;
}
