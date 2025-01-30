#include "./../minishell.h"

void exec_pipe(t_token *token)
{
    printf("Executando PIPE: %s\n", token->cmd);
}