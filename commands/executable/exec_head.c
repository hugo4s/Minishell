#include "./../../minishell.h"

void exec_head(t_token *token)
{
    printf("Executando HEAD com: %s\n", token->cmd);
}