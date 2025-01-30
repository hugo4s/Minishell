#include "./../../minishell.h"

void exec_touch(t_token *token)
{
    printf("Executando TOUCH com: %s\n", token->cmd);
}