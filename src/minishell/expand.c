#include "minishell.h"


t_command	*ft_expand(t_command *list, t_ms *ms, int i)
{
	int		j;
	char	*temp;
	char	*expand;
	char	*result;

	result = NULL;
	if (!ms->env || !list->line)
		return (list);
	if (list->line[i])
	{
		while (list->line[i] && list->line[i] != '$')
		{
			if (list->line[i - 1] == '\\')
				break ;
			else
				i++;
		}
		if ((int)ft_strlen(list->line) == i)
			return (list);
		result = ft_substr(list->line, 0, i);
		j = 0;
		while (list->line[i + j] && list->line[i + j] != ' ' && list->line[i + j] != '\'' && list->line[i + j] != '\"')
			if (list->line[i + ++j] == '$')
				break ;
		temp = ft_substr(list->line, i, j);
		if (temp[1] == '?' && !temp[2])
		{
			free(temp);
			temp = ft_itoa(ms->status);
			result = ft_strjoin_free(result, temp);
			free(temp);
		}
		else if (temp[0] == '$' && (!temp[1] || !ft_isalnum(temp[1])))
		{
			result = ft_strjoin_free(result, temp);
			free(temp);
		}
		else if (temp[1] != '$' && temp[1])
		{
			if (temp[ft_strlen(temp) - 1] == '\\')
				temp[ft_strlen(temp) - 1] = '\0';
			if (temp && list->line[i - 1] != '\\')
			{
				expand = ft_get_env_key(ms->env, &temp[1]);
				free(temp);
			}
			else
				expand = temp;
			if (expand)
			{
				result = ft_strjoin_free(result, expand);
				free(expand);
			}
		}
		else
			expand = temp;
		if (j > i)
			result = ft_strjoin_free(result, &list->line[i + j]);
		else
			result = ft_strjoin_free(result, &list->line[i + j]);
		free(list->line);
		list->line = result;
		ft_expand(list, ms, i + j + 1);
	}
	return (list);
}
