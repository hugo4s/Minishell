#include "minishell.h"

static void handle_command_token(t_token *current, t_token **last_cmd,
    int *command_seen)
{
    current->args_file = malloc(sizeof(char *) * 2);
    if (!current->args_file)
        return ;
    current->args_file[0] = strdup(current->cmd);
    current->args_file[1] = NULL;
    if (is_builtin_command(current->cmd) || is_exec_command(current->cmd))
    {
        set_command_type(current);
        *command_seen = 1;
        *last_cmd = current;
    }
    else
    {
        current->type = CMD_NONE;
        fprintf(stderr, "%s: command not found\n", current->cmd);
    }
}

static void handle_argument_token(t_token *current, t_token *prev,
    t_token *last_cmd)
{
    if (prev && prev->type == CMD_REDIRECT)
    {
        current->type = CMD_ARG_FILE;
        if (prev)
            add_to_args_file(prev, current->cmd);
    }
    else if (last_cmd)
    {
        current->type = CMD_ARG;
        add_to_args_file(last_cmd, current->cmd);
    }
}

void process_token(t_token *current, t_token *prev,
    t_token **last_cmd, int *command_seen)
{
    if (current->cmd[0] == '|')
    {
        current->type = CMD_PIPE;
        *command_seen = 0;
        *last_cmd = NULL;
    }
    else if (current->cmd[0] == '<' || current->cmd[0] == '>')
    {
        current->type = CMD_REDIRECT;
        *last_cmd = NULL;
    }
    else if (!(*command_seen))
        handle_command_token(current, last_cmd, command_seen);
    else
        handle_argument_token(current, prev, *last_cmd);
}
