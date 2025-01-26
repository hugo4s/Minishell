#include "minishell.h"

static char	*filler(char *input, int pos)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(ft_strlen(input) + 3, sizeof (char));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++j < pos)
		ret[j] = input[++i];
	i++;
	ret[j++] = -1;
	ret[j++] = input[i++];
	if (input[i] == input[i - 1] && input[i] != '|')
		ret[j++] = input[i++];
	ret[j++] = -1;
	while (input[i])
		ret[j++] = input[i++];
	ret[j] = '\0';
	input = free_ptr(input);
	return (ret);
}

char	**lexer(char *input)
{
	int		i;
	int		quotes;
	char	*temp;
	char	**ret;

	i = -1;
	quotes = 0;
	temp = ft_strdup(input);
	while (temp && temp[++i])
	{
		if ((temp[i] == '|' || temp[i] == '>' || temp[i] == '<' ) && !quotes)
		{
			temp = filler(temp, i);
			i = i + 2;
		}	
		else if (temp[i] == '\"' || temp[i] == '\'')
			quotes = check_quotes(temp[i], quotes);
	}
	if (quotes)
		temp = free_ptr(temp);
	ret = ft_split(temp, -1);
	temp = free_ptr(temp);
	return (ret);
}