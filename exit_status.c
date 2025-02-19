#include "minishell.h"

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int sig)
{
    (void)sig;
}

void setup_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}

void reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void execute_command(t_mini *ms, t_token *cmd)
{
    pid_t pid;
    int status;

    if (!cmd || !cmd->cmd)
        return;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    pid = fork();
    if (pid == 0)
    {
        reset_signals();
        
        execvp(cmd->cmd, cmd->args_file);
        perror("minishell");
        exit(127);
    }
    else if (pid > 0)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            ms->exit_status = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGINT)
            {
                ms->exit_status = 130;
                write(1, "\n", 1);
            }
            else if (WTERMSIG(status) == SIGQUIT)
            {
                ms->exit_status = 131;
                write(1, "Quit (core dumped)\n", 19);
            }
            else
                ms->exit_status = 128 + WTERMSIG(status);
        }
        
        setup_signals();
    }
    else
    {
        perror("minishell: fork");
        ms->exit_status = 1;
        setup_signals();
    }
}