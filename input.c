#include "minishell.h"

char *get_input(t_mini *ms, char *prompt)
{
    char *input;

    (void)(ms);
    input = readline(prompt);
    if (input)
    {
        add_history(input);
    }
    return input;
}