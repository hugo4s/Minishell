#include "./../minishell.h"

static int is_command(const char *cmd)
{
    static const char *commands[] = {
        "ls", "cat", "mkdir", "rm", "cp", "mv",
        "grep", "wc", "ps", "head", "tail",
        "sort", "clear", "touch", NULL
    };
    int i;

    i = 0;
    while (commands[i])
    {
        if (strcmp(cmd, commands[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

void exec_command(t_token *token)
{
    if (!is_command(token->cmd))
        return;
        
    if (strcmp(token->cmd, "ls") == 0)
        exec_ls(token);
    else if (strcmp(token->cmd, "cat") == 0)
        exec_cat(token);
    else if (strcmp(token->cmd, "mkdir") == 0)
        exec_mkdir(token);
    else if (strcmp(token->cmd, "rm") == 0)
        exec_rm(token);
    else if (strcmp(token->cmd, "cp") == 0)
        exec_cp(token);
    else if (strcmp(token->cmd, "mv") == 0)
        exec_mv(token);
    else if (strcmp(token->cmd, "grep") == 0)
        exec_grep(token);
    else if (strcmp(token->cmd, "wc") == 0)
        exec_wc(token);
    else if (strcmp(token->cmd, "ps") == 0)
        exec_ps(token);
    else if (strcmp(token->cmd, "head") == 0)
        exec_head(token);
    else if (strcmp(token->cmd, "tail") == 0)
        exec_tail(token);
    else if (strcmp(token->cmd, "sort") == 0)
        exec_sort(token);
    else if (strcmp(token->cmd, "clear") == 0)
        exec_clear();
    else if (strcmp(token->cmd, "touch") == 0)
        exec_touch(token);
}