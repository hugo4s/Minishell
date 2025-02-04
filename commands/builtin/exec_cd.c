#include "./../../minishell.h"

char	*get_new_cwd(char *buffer);
int		ft_strcmp(char *s1, char *s2);
char	*get_user(char **envp);

void	exec_cd(t_token *token, t_mini mini)
{
	char	*buffer;
	char	*user;

	buffer = NULL;
	if (token->next)
	{
		if (ft_strcmp(token->next->cmd, "..") == 0)
		{
			buffer = getcwd(buffer, 0);
			buffer = get_new_cwd(buffer);
			chdir(buffer);
		}
		if (ft_strcmp(token->next->cmd, "~") == 0)
		{
			user = get_user(mini.envp);
			buffer = ft_strjoin("/home/", user);
			free(user);
			chdir(buffer);
			free(buffer);
		}
		printf("Executando CD com: %s\n", buffer);
	}
}

char	*get_user(char **envp)
{
	int		i;
	char	*user;	

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "USER=", 5) == 0)
		{	
			user = ft_strdup(envp[i] + 5);
			return (user);
		}		
		i++;
	}
	return (NULL);
}

char	*get_new_cwd(char *buffer)
{
	int	i;

	i = ft_strlen(buffer);
	i--;
	while (i >= 0)
	{
		if (buffer[i] == '/')
		{
			if (i == 0)
				buffer[++i] = '\0';
			else
				buffer[i] = '\0';
			break ;
		}
		i--;
	}
	return (buffer);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
	{
		printf("Error strcmp: NULL string");
		return (1);
	}
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (0);
	return (1);
}
