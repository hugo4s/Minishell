#include "./../../minishell.h"

void exec_ls(t_token *token)
{
    printf("Executando LS com: %s\n", token->cmd);
}