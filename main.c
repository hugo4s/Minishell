#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
    t_mini ms;

    (void)(argc);
    (void)(argv);
    ms = init(envp);
    while(1)
    {
        ms.input = get_input(&ms, ms.prompt);
        if (ms.input)
        {
            ms.token = lexer(ms.input);
            if (ms.token)
            {
				parser(&ms);
				exec(&ms);
            }
        }
        for (t_token *current = ms.token; current != NULL; current = current->next)
		{
			if(current->type != CMD_NONE)
			{
				printf("%s\n", current->cmd);
				printf("%d\n", current->type);
			}
        }
    }
}