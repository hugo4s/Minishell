#include "./../../minishell.h"

void exec_unset(t_token *token)
{
    printf("Executando UNSET com: %s\n", token->cmd);
}