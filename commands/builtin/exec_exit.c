#include "./../../minishell.h"

void exec_exit(t_token *token)
{
    printf("Executando EXIT com: %s\n", token->cmd);
}
