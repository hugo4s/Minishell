#include "minishell.h"

t_env	*get_envp(char **envp);
void	create_node(t_env **head, char *s);
t_env	*ft_last(t_env *head);

t_mini init(char **envp)
{
    t_mini ms;

    ms.input = NULL;
    ms.envp = get_envp(envp);
    ms.token = NULL;
    ms.prompt = "minishell$ ";
	ms.exit_status = 0;
	ms.in_quotes = 0;
    return (ms);
}

t_env	*get_envp(char **envp)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while(envp[i])
	{
		create_node(&head, envp[i]);
		i++;
	}
	return (head);
}

char	*get_var(char *s)
{
	int		i;
	char	*var;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '=')
		i++;
	var = malloc(i + 1);	
	i = 0;
	while (s[i] != '=')
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

void	create_node(t_env **head, char *s)
{
	t_env	*node;
	t_env	*last;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->content = s;
	node->var = get_var(s);
	node->next = NULL;
	if (!(*head))
	{
		*head = node;		
		node->prev = NULL;
	}
	else
	{
		last = ft_last(*head);
		node->prev = last;
		last->next = node;
	}
}

t_env	*ft_last(t_env *head)
{
	t_env	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current && current->next)
		current = current->next;
	return (current);
}
