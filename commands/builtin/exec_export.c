/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:37:34 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/13 16:53:10 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	swap_var(t_env *current, t_env *next, t_env **head);
void	print_export(t_env *head);
void	order_var(t_mini *mini);
int		check_syntax(char *cmd);
int		check_alpha(char *cmd);
void	create_export(char *cmd, t_mini *mini);
void	create_node2(char *var, char *content, t_env *head);

void	exec_export(t_token *token, t_mini *mini)
{
	order_var(mini);
	if (!token->next)
		print_export(mini->export);
	else
	{
		if (!check_syntax(token->next->cmd))
			return ;
		create_export(token->next->cmd, mini);
	}
}

void	create_export(char *cmd, t_mini *mini)
{
	char	*var;
	char	*content;
	char	*temp;

	temp = ft_strchr(cmd, '=');
	if (!temp)
	{
		var = ft_strdup(cmd);
		content = NULL;
	}
	else if (!*(temp + 1))
	{
		content = ft_strdup(cmd);
		*temp = '\0';
		var = ft_strdup(cmd);
	}
	else
	{
		content = ft_strdup(cmd);
		*temp = '\0';
		var = ft_strdup(cmd);
	}
	create_node2(var, content, mini->envp);
	create_node2(var, content, mini->export);
}

void	create_node2(char *var, char *content, t_env *head)
{
	t_env	*node;
	t_env	*last;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->content = content;
	node->var = var;
	node->next = NULL;
	last = ft_last(head);
	node->prev = last;
	last->next = node;
}

int	check_syntax(char *cmd)
{
	if (ft_isdigit(cmd[0]) || !check_alpha(cmd))
	{
		printf("minishell: export: `%s': not a valid identifier\n", cmd);
		return (0);
	}
	return (1);
}

int	check_alpha(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '=' && cmd[i] != '\"' && !ft_isalpha(cmd[i])
			&& !ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	order_var(t_mini *mini)
{
	t_env	*head;
	t_env	*current;

	head = mini->export;
	current = head;
	while (current && current->next)
	{
		if (ft_strcmp(current->var, current->next->var) > 0)
		{
			swap_var(current, current->next, &head);
			current = head;
		}
		else
			current = current->next;
	}
	mini->export = head;
}

void	print_export(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i = ft_strlen(head->var) + 1;
		if (!head->content)
			printf("declare -x %s\n", head->var);
		else
			printf("declare -x %s=\"%s\"\n", head->var, head->content + i);
		head = head->next;
	}
}

void	swap_var(t_env *current, t_env *next, t_env **head)
{
	if (*head == current)
	{
		*head = next;
	}
	if (current->prev)
	{
		current->prev->next = next;
	}
	if (next->next)
	{
		next->next->prev = current;
	}
	current->next = next->next;
	next->prev = current->prev;
	next->next = current;
	current->prev = next;
	if (!next->next)
	{
		current->next = NULL;
	}
}
