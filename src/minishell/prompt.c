#include "minishell.h"

static int	ft_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}

static int	ft_expand(t_ms *ms, int i)
{
	int		j;
	char	*temp;
	char	*expand;
	char	*result;

	result = NULL;
	if (!ms->env || !ms->list->line)
		return (0);
	if (ms->list->line[i])
	{
		j = 0;
		while (ms->list->line[i + j] && ms->list->line[i + j] != '$')
			j++;
		if ((int)ft_strlen(ms->list->line) == j)
			return (0);
		result = ft_substr(ms->list->line, 0, j);
		i += j;
		j = 0;
		while (ms->list->line[i + j] && ms->list->line[i + j] != ' ' && ms->list->line[i + j] != '\\')
			j++;
		if (j - 1 < 0)
		temp = NULL;
		else
			temp = ft_substr(ms->list->line, i + 1, j - 1);
		if (temp)
		{
			//printf("temp:(%s)\n", temp);
			expand = ft_get_env_key(ms->env, temp);
			free(temp);
		}
		else
		{
			temp = ft_strjoin("$", temp);
			expand = temp;
		}
		if (expand)
			result = ft_strjoin(result, expand);
		result = ft_strjoin(result, &ms->list->line[i + j]);
		free(ms->list->line);
		ms->list->line = result;
		ft_expand(ms, 0);
	}
	return (1);
}

void	ft_prompt(t_ms *ms)
{
	int		j;
	char	*temp;

	signal(SIGINT, ft_handler);
	rl_replace_line("", 0);
	if (ms->list->line)
		free(ms->list->line);
	ms->list->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!ms->list->line)
		return ;
	ms->list->line[ft_strlen(ms->list->line) + 1] = 0;
	if (!ft_is_empty(ms->list->line))
		add_history(ms->list->line);
	j = -1;
	while (ms->list->line[++j])
	{
		if (ms->list->line[j] == '\"' && ms->list->line[j - 1] && ms->list->line[j - 1] != '\\')
		{
			temp = ft_substr(ms->list->line, 0, j);
			temp = ft_strjoin(temp, &ms->list->line[j + 1]);
			free(ms->list->line);
			ms->list->line = temp;
			while (ms->list->line[++j] && ms->list->line[j] != '\"')
			{
				if (ms->list->line[j] == '\'')
					while (ms->list->line[j + 1] && ms->list->line[j + 1] != '\"' && ms->list->line[j + 1] != '\'')
						j++;
				else if (ms->list->line[j] == '$')
					while (ms->list->line[j] && ms->list->line[j] != '\"' && ms->list->line[j] != ' ')
						j++;
				else
				{
					temp = ft_strjoin(ft_substr(ms->list->line, 0, j), "\\");
					temp = ft_strjoin(temp, &ms->list->line[j]);
					free(ms->list->line);
					ms->list->line = temp;
					j++;
				}
				if (ms->list->line[j] == '\"')
					j--;
			}
			if (ms->list->line[j] == '\"')
			{
				temp = ft_substr(ms->list->line, 0, j);
				temp = ft_strjoin(temp, &ms->list->line[j + 1]);
				free(ms->list->line);
				ms->list->line = temp;
			}
		}
	}

	// j = 0;
	// while (ms->list->line[j])
	// {
	// 	if (ms->list->line[j] == '\"' && ms->list->line[j - 1] && ms->list->line[j - 1] != '\\')
	// 	{
	// 		temp = ft_strjoin(ft_substr(ms->list->line, 0, j), &ms->list->line[j + 1]);
	// 		free(ms->list->line);
	// 		ms->list->line = temp;
	// 		while (ms->list->line[++j] && ms->list->line[j] != '\"')
	// 		{
	// 			if (ms->list->line[j] == ' ')
	// 			{
	// 				temp = ft_strjoin(ft_substr(ms->list->line, 0, j), "\\");
	// 				temp = ft_strjoin(temp, &ms->list->line[j]);
	// 				free(ms->list->line);
	// 				ms->list->line = temp;
	// 			}
	// 			j++;
	// 		}
	// 		if (ms->list->line[j] == '\"')
	// 		{
	// 			temp = ft_substr(ms->list->line, 0, j);
	// 			temp = ft_strjoin(temp, &ms->list->line[j + 1]);
	// 			free(ms->list->line);
	// 			ms->list->line = temp;
	// 		}
	// 	}
	// 	j++;
	// }
	ft_expand(ms, 0);
}
