#include "./../minishell.h"

void exec_heredoc(t_token *token)
{
    printf("Executando HEREDOC: %s\n", token->cmd);
}