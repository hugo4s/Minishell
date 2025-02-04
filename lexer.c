#include "minishell.h"

static char **free_mat(char **mat)
{
    int i;

    if (!mat)
        return NULL;
    i = 0;
    while (mat[i])
    {
        free(mat[i]);
        i++;
    }
    free(mat);
    return NULL;
}

t_token *create_new_token(char *cmd)
{
    t_token *new_token;

    if (!(new_token = malloc(sizeof(t_token))))
        return NULL;
    if (!(new_token->cmd = ft_strdup(cmd)))
    {
        free(new_token);
        return NULL;
    }
    new_token->next = NULL;
    return new_token;
}

t_token *lexer(char *input)
{
    t_token *head = NULL;
    t_token *tail = NULL;
    char **mat = ft_split(input, ' ');
    int i = 0;

    while (mat[i])
    {
        t_token *new_token = create_new_token(mat[i]);
        if (!new_token)
        {
            free_mat(mat);
            exit(1);
        }

        if (!head)
        {
            head = new_token;
            tail = new_token;
        }
        else
        {
            tail->next = new_token;
			new_token->prev = tail;
            tail = new_token;
        }
        i++;
    }
    free_mat(mat);
    return head;
}

