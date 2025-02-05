#include "./../minishell.h"

void exec_command(t_token *token)
{
    pid_t pid;
    int status;

    if (!token || !token->cmd)
        return;

    pid = fork();
    if (pid < 0)
    {
        perror("Erro ao criar processo");
        return;
    }
    if (pid == 0)
    {
        execvp(token->cmd, token->args_file);
        perror("Erro ao executar comando");
        exit(1);
    }
    else
        waitpid(pid, &status, 0);
}