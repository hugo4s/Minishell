#include "minishell.h"

static int is_pipe_command(const t_token *cmd) {
    return (cmd && cmd->cmd && strcmp(cmd->cmd, "|") == 0);
}

static int is_exec_command(const t_token *cmd) {
    return (cmd && cmd->cmd && cmd->prev == NULL);  // First command in sequence
}

static int is_buildin_command(const t_token *cmd) {
    if (!cmd || !cmd->cmd)
        return 0;
    
    const char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    
    for (int i = 0; builtins[i]; i++) {
        if (strcmp(cmd->cmd, builtins[i]) == 0)
            return 1;
    }
    return 0;
}

static int is_arg_command(const t_token *cmd) {
    return (cmd && cmd->cmd && cmd->prev && 
            cmd->cmd[0] != '<' && cmd->cmd[0] != '>' && 
            !is_pipe_command(cmd));
}

static int is_arg_file_command(const t_token *cmd) {
    return (cmd && cmd->cmd && (
        (cmd->prev && (strcmp(cmd->prev->cmd, "<") == 0 || 
                      strcmp(cmd->prev->cmd, ">") == 0 || 
                      strcmp(cmd->prev->cmd, ">>") == 0))));
}

static int is_redirect_command(const t_token *cmd) {
    return (cmd && cmd->cmd && (
        strcmp(cmd->cmd, "<") == 0 || 
        strcmp(cmd->cmd, ">") == 0 || 
        strcmp(cmd->cmd, ">>") == 0));
}

static int is_heredoc_command(const t_token *cmd) {
    return (cmd && cmd->cmd && strcmp(cmd->cmd, "<<") == 0);
}

void parser(t_mini *ms) {
    if (!ms || !ms->token)
        return;

    t_token *current = ms->token;
    while (current) {
        if (is_pipe_command(current)) {
            current->type = CMD_PIPE;
        }
        else if (is_buildin_command(current)) {
            current->type = CMD_BUILDIN;
        }
        else if (is_exec_command(current)) {
            current->type = CMD_EXEC;
        }
        else if (is_arg_command(current)) {
            current->type = CMD_ARG;
        }
        else if (is_arg_file_command(current)) {
            current->type = CMD_ARG_FILE;
        }
        else if (is_redirect_command(current)) {
            current->type = CMD_REDIRECT;
        }
        else if (is_heredoc_command(current)) {
            current->type = CMD_HEREDOC;
        }
        else {
            current->type = CMD_NONE;
        }
        
        current = current->next;
    }
}