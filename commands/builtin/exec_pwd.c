#include "./../../minishell.h"

void exec_pwd(t_token *token)
{
    printf("Executando PWD com: %s\n", token->cmd);
}