/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:12:54 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/13 16:24:46 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

char	*print_echo(char *input, int *i, char *var, t_mini *mini);
void	echo_others(t_token *token, t_mini *mini);

void	exec_echo(t_token *token, t_mini *mini)
{
	t_token	*next;	

	next = token->next;
	if (!next)
		printf("\n");
	else if (ft_strcmp(next->cmd, "~") == 0)
		printf("%s\n", expand_var("HOME", mini->envp));
	else
		echo_others(token, mini);
}

void	echo_others(t_token *token, t_mini *mini)
{
	char	*input;
	char	*var;
	int		i;

	i = 0;
	(void)token;
	input = mini->input + 5;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			i++;
		else if (input[i] == '$')
		{
			var = ft_strdup(&input[++i]);
			if (!print_echo(input, &i, var, mini) && input[i])
				i++;			
		}
		else
		{
			printf("%c", input[i]);
			i++;
		}
	}
	printf("\n");
}

char	*print_echo(char *input, int *i, char *var, t_mini *mini)
{
	char	*s;
	int		j;
	
	j = 0;
	while (var[j] && var[j] != ' ')
		j++;
	var[j] = '\0';		
	s = expand_var(var, mini->envp);
	free(var);
	if (s)
	{
		printf("%s", s);
		free(s);
	}	
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	return (s);
}
