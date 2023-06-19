#include "minishell.h"

t_ms	*g_ms;

static int	ft_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}

static t_command	*ft_expand(t_command *list, t_env *env, int i)
{
	int		j;
	char	*temp;
	char	*expand;
	char	*result;

	result = NULL;
	if (!env || !list->line)
		return (list);
	if (list->line[i])
	{
		printf("line:(%s)\n", list->line);
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
			if (list->line[i + ++j] == '$' && list->line[i + j - 1] != '\\')
				break ;
		temp = ft_substr(list->line, i, j);
		if (temp[ft_strlen(temp) - 1] == '\\')
			temp[ft_strlen(temp) - 1] = '\0';
		printf("temp:(%s)\n", temp);
		if (temp && list->line[i - 1] != '\\')
		{
			expand = ft_get_env_key(env, &temp[1]);
			free(temp);
		}
		else
			expand = temp;
		if (expand)
		{
			result = ft_strjoin_free(result, expand);
			free(expand);
		}
		result = ft_strjoin_free(result, &list->line[i + j]);
		free(list->line);
		list->line = result;
		ft_expand(list, env, i + j + 1);
	}
	return (list);
}

static t_command	*ft_comillas(t_command *list)
{
	int		j;
	char	*temp;

	j = 0;
	if (!list->line)
		return (NULL);
	while (list->line[j])
	{
		if (list->line[j] == '\'')
		{
			temp = ft_strjoin(ft_substr(list->line, 0, j), "");
			temp = ft_strjoin_free(temp, &list->line[j + 1]);
			free(list->line);
			list->line = temp;
			while (list->line[j] && list->line[j] != '\'')
			{
				if (list->line[j] == '$' && list->line[j - 1] != '\\')
				{
					temp = ft_strjoin(ft_substr(list->line, 0, j), "\\");
					temp = ft_strjoin_free(temp, &list->line[j]);
					free(list->line);
					list->line = temp;
					j += 2;
				}
				else
					j++;
			}
			if (list->line[j] == '\'')
			{
				temp = ft_strjoin(ft_substr(list->line, 0, j), "");
				temp = ft_strjoin_free(temp, &list->line[j + 1]);
				free(list->line);
				list->line = temp;
			}
		}
		///////
		if (list->line[j] == '\"')
		{
			temp = ft_substr(list->line, 0, j);
			temp = ft_strjoin_free(temp, &list->line[j + 1]);
			free(list->line);
			list->line = temp;
			while (list->line[j] && list->line[j] != '\"')
			{
				if (list->line[j] == '$')
				{
					while (list->line[j] && list->line[j] != ' ' && list->line[j] != '\"')
						j++;
				}
				else
				{
					if (list->line[j] && list->line[j - 1] != '\\')
					{
						temp = ft_strjoin(ft_substr(list->line, 0, j), "\\");
						temp = ft_strjoin_free(temp, &list->line[j]);
						free(list->line);
						list->line = temp;
						j += 2;
					}
					else
						j++;
				}
			}
		}
		if (list->line[j] == '\"')
		{
			temp = ft_strjoin(ft_substr(list->line, 0, j), "");
			temp = ft_strjoin_free(temp, &list->line[j + 1]);
			free(list->line);
			list->line = temp;
		}
		j++;
	}

	return (list);
}

static t_command	**ft_split_line(t_command **list, char *line)
{
	int		i;
	int		total_split;
	char	**line_split;

	total_split = -1;
	line_split = ft_split(line, '|');
	if (!line_split)
		return (NULL);
	i = 0;
	while (line_split[++i])
		;
	list = ft_calloc(i + 1, sizeof(t_command *));
	i = -1;
	while (line_split[++i])
		list[i] = ft_calloc(1, sizeof(t_command));
	i = -1;
	while (line_split[++i])
	{
		list[i]->line = ft_strdup(line_split[i]);
		if (i + 1 <= total_split)
			list[i]->next = NULL;
		else
			list[i]->next = list[i + 1];
	}
	return (ft_free_matrix(line_split), list);
}

void	ft_prompt(t_ms *g_ms)
{
	int		i;

	signal(SIGINT, ft_handler);
	rl_replace_line("", 0);
	if (g_ms->line)
		free(g_ms->line);
	g_ms->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!g_ms->line)
		return ;
	if (!ft_is_empty(g_ms->line))
		add_history(g_ms->line);
	g_ms->list = ft_split_line(g_ms->list, g_ms->line);
	if (!g_ms->list)
		return ;
	i = 0;
	while (g_ms->list[i])
	{
		g_ms->list[i] = ft_comillas(g_ms->list[i]);
		g_ms->list[i] = ft_expand(g_ms->list[i], g_ms->env, 0);
		i++;
	}
	return ;
}
