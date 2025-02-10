/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:21:07 by ruida-si          #+#    #+#             */
/*   Updated: 2025/02/08 19:55:00 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	exec_cd_4(t_token *token, t_mini *mini);
void	exec_cd_3(t_token *token, t_mini *mini);
void	exec_cd_2(t_token *token, t_mini *mini);
void	exec_cd_1(t_token *token, t_mini *mini);

void	exec_cd(t_token *token, t_mini *mini)
{
	if (!token->next || ft_strcmp(token->next->cmd, "~") == 0)
		exec_cd_1(token, mini);
	else if (ft_strcmp(token->next->cmd, "..") == 0)
		exec_cd_2(token, mini);
	else if (ft_strcmp(token->next->cmd, ".") == 0)
	{
		return ;
	}
	else if (ft_strcmp(token->next->cmd, "-") == 0)
		exec_cd_4(token, mini);
	else
		exec_cd_3(token, mini);
}

void	exec_cd_4(t_token *token, t_mini *mini)
{
	char	*oldpwd;
	char	*pwd;

	(void)token;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		printf("Not found OLDPWD");
		return ;
	}
	pwd = get_old_pwd(mini->envp);
	if (!pwd)
	{
		printf("Not found oldpwd\n");
		return ;
	}
	if (chdir(pwd) == -1)
	{
		printf("cd: %s: %s\n", token->next->cmd, strerror(errno));
		return ;
	}
	update_var(oldpwd, pwd, mini);
	free_pwd(oldpwd, pwd);
}

void	exec_cd_3(t_token *token, t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;
	char	*temp;

	pwd = NULL;
	temp = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return ;
	}
	temp = ft_strjoin(oldpwd, "/");
	pwd = ft_strjoin(temp, token->next->cmd);
	free(temp);
	if (chdir(pwd) == -1)
	{
		printf("cd: %s: %s\n", token->next->cmd, strerror(errno));
		free_pwd(oldpwd, pwd);
		return ;
	}
	update_var(oldpwd, pwd, mini);
	free_pwd(oldpwd, pwd);
}

void	exec_cd_2(t_token *token, t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;

	(void)token;
	pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return ;
	}
	pwd = get_new_cwd(oldpwd);
	if (chdir(pwd) == -1)
	{
		perror("chdir failed");
		return ;
	}
	update_var(oldpwd, pwd, mini);
	free_pwd(oldpwd, pwd);
}

void	exec_cd_1(t_token *token, t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;
	char	*user;

	(void)token;
	pwd = NULL;
	user = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd failed");
		return ;
	}
	user = getenv("USER");
	if (!user)
		return ;
	pwd = ft_strjoin("/home/", user);
	if (chdir(pwd) == -1)
	{
		perror("chdir failed");
		return ;
	}
	update_var(oldpwd, pwd, mini);
	free_pwd(oldpwd, pwd);
}
