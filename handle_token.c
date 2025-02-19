#include "minishell.h"

static char *process_quotes(char *str, int is_single_quote, t_mini *ms)
{
    char *result;
    char *temp;
    int len;
    
    if (!str)
        return NULL;
    result = strdup(str + 1);
    if (!result)
        return NULL;
    len = strlen(result);
    if (len > 0 && result[len - 1] == (is_single_quote ? '\'' : '"'))
        result[len - 1] = '\0';
    
    if (!is_single_quote && ms)
    {
        char *pos = strstr(result, "$?");
        if (pos)
        {
            int prefix_len = pos - result;
            char exit_str[16];
            sprintf(exit_str, "%d", ms->exit_status);
            int exit_len = strlen(exit_str);
            int suffix_len = strlen(pos + 2);
            
            temp = malloc(prefix_len + exit_len + suffix_len + 1);
            if (!temp)
            {
                free(result);
                return NULL;
            }
            strncpy(temp, result, prefix_len);
            strcpy(temp + prefix_len, exit_str);
            strcpy(temp + prefix_len + exit_len, pos + 2);
            free(result);
            result = temp;
        }
    }
    
    return result;
}

static void free_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

static char **env_to_array(t_env *env)
{
    int count = 0;
    t_env *temp = env;
    char **env_array;
    
    // Count environment variables
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    
    // Allocate array
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return NULL;
    
    // Fill array
    temp = env;
    count = 0;
    while (temp)
    {
        size_t len = strlen(temp->var) + strlen(temp->content) + 2;
        env_array[count] = malloc(len);
        if (!env_array[count])
        {
            free_array(env_array);
            return NULL;
        }
        snprintf(env_array[count], len, "%s=%s", temp->var, temp->content);
        temp = temp->next;
        count++;
    }
    env_array[count] = NULL;
    
    return env_array;
}

static int execute_subshell(char *command, t_mini *ms)
{
    pid_t pid;
    int status;
    char **args;
    char **env_array;
    
    args = ft_split(command, ' ');
    if (!args)
        return (1);
    
    env_array = env_to_array(ms->envp);
    if (!env_array)
    {
        free_array(args);
        return (1);
    }
    
    pid = fork();
    if (pid == -1)
    {
        free_array(args);
        free_array(env_array);
        return (1);
    }
    
    if (pid == 0)
    {
        if (execve(args[0], args, env_array) == -1)
        {
            fprintf(stderr, "minishell: %s: %s\n", args[0], strerror(errno));
            free_array(args);
            free_array(env_array);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        free_array(args);
        free_array(env_array);
        
        if (WIFEXITED(status))
            ms->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            ms->exit_status = WTERMSIG(status) + 128;
    }
    
    return (0);
}

void add_to_args_file(t_token *token, char *arg)
{
    int i;
    char **new_args;
    
    for (i = 0; token->args_file[i]; i++)
        ;
    
    new_args = malloc(sizeof(char *) * (i + 2));
    if (!new_args)
        return;
    
    for (i = 0; token->args_file[i]; i++)
        new_args[i] = token->args_file[i];
    
    new_args[i] = strdup(arg);
    new_args[i + 1] = NULL;
    
    free(token->args_file);
    token->args_file = new_args;
}

static void handle_command_token(t_token *current, t_token **last_cmd,
    int *command_seen, t_mini *ms)
{
    current->args_file = malloc(sizeof(char *) * 2);
    if (!current->args_file)
        return;

    if (current->cmd[0] == '\'') {
        current->type = CMD_SINGLE_QUOTE;
        current->args_file[0] = process_quotes(current->cmd, 1, ms);
    }
    else if (current->cmd[0] == '"') {
        current->type = CMD_DOUBLE_QUOTE;
        current->args_file[0] = process_quotes(current->cmd, 0, ms);
    }
    else if (strncmp(current->cmd, "./minishell", 11) == 0) {
        current->type = CMD_SUBSHELL;
        current->args_file[0] = strdup(current->cmd);
        execute_subshell(current->cmd, ms);
        *command_seen = 1;
        *last_cmd = current;
    }
    else {
        current->args_file[0] = strdup(current->cmd);
        
        if (is_builtin_command(current->cmd) || is_exec_command(current->cmd)) {
            set_command_type(current);
            *command_seen = 1;
            *last_cmd = current;
        }
        else {
            current->type = CMD_NONE;
            fprintf(stderr, "%s: command not found\n", current->cmd);
        }
    }
    current->args_file[1] = NULL;
}

static void handle_argument_token(t_token *current, t_token *prev,
    t_token *last_cmd, t_mini *ms)
{
    char *processed_arg = NULL;

    if (strcmp(current->cmd, "$?") == 0) {
        current->type = CMD_EXIT_STATUS;
        char exit_status[16];
        sprintf(exit_status, "%d", ms->exit_status);
        processed_arg = strdup(exit_status);
    }
    else if (current->cmd[0] == '\'') {
        current->type = CMD_SINGLE_QUOTE;
        processed_arg = process_quotes(current->cmd, 1, ms);
    }
    else if (current->cmd[0] == '"') {
        current->type = CMD_DOUBLE_QUOTE;
        processed_arg = process_quotes(current->cmd, 0, ms);
    }
    else {
        processed_arg = strdup(current->cmd);
    }

    if (prev && prev->type == CMD_REDIRECT) {
        current->type = CMD_ARG_FILE;
        if (prev && processed_arg)
            add_to_args_file(prev, processed_arg);
    }
    else if (last_cmd && processed_arg) {
        current->type = CMD_ARG;
        add_to_args_file(last_cmd, processed_arg);
    }

    free(processed_arg);
}

void process_token(t_token *current, t_token *prev,
    t_token **last_cmd, int *command_seen, t_mini *ms)
{
    if (strcmp(current->cmd, "$?") == 0) {
        printf("%d\n", ms->exit_status);
        current->type = CMD_EXIT_STATUS;
        *command_seen = 1;
        return;
    }

    if (current->cmd[0] == '\\') {
        current->type = CMD_NONE;
        return;
    }
    
    if (current->cmd[0] == ';') {
        current->type = CMD_NONE;
        return;
    }

    if (current->cmd[0] == '|') {
        current->type = CMD_PIPE;
        *command_seen = 0;
        *last_cmd = NULL;
    }
    else if (current->cmd[0] == '<' || current->cmd[0] == '>') {
        current->type = CMD_REDIRECT;
        if (current->cmd[1] == '<')
            current->type = CMD_HEREDOC;
        *last_cmd = NULL;
    }
    else if (!(*command_seen))
        handle_command_token(current, last_cmd, command_seen, ms);
    else
        handle_argument_token(current, prev, *last_cmd, ms);
}