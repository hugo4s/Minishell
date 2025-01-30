#include "./../../minishell.h"

void exec_echo(t_token *token)
{
    printf("Executando ECHO com: %s\n", token->cmd);
}