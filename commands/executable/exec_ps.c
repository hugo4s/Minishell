#include "./../../minishell.h"

void exec_ps(t_token *token)
{
    printf("Executando PS com: %s\n", token->cmd);
}