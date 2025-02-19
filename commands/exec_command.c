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
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        
        execvp(token->cmd, token->args_file);
        perror("Erro ao executar comando");
        exit(127);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        
        waitpid(pid, &status, 0);

        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN); // Continua ignorando Ctrl+\ no shell
    }
}
