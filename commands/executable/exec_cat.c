#include "./../../minishell.h"

void cat_file(const char *filename)
{
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        write(STDERR_FILENO, "cat: ", 5);
        write(STDERR_FILENO, filename, strlen(filename));
        write(STDERR_FILENO, ": No such file or directory\n", 27);
        return;
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
        write(STDOUT_FILENO, buffer, bytes_read);

    if (bytes_read == -1)
        write(STDERR_FILENO, "cat: Error reading file\n", 23);
    close(fd);
}

static void cat_stdin(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
        write(STDOUT_FILENO, buffer, bytes_read);
}

void exec_cat(t_token *token)
{
    if (!token || !token->args_file)
        return;

    char **args = token->args_file;
    
    if (!args[0])
        return;

    if (!args[1])
    {
        cat_stdin();
        return;
    }

    int i = 1;
    while (args[i])
    {
        cat_file(args[i]);
        i++;
    }
}