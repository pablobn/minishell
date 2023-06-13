#include "minishell.h"

static int	ft_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}

static t_command	*ft_expand(t_command *list, t_env *env)
{
	int		j;
	char	*temp;
	char	*expand;
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (!env || !list->line)
		return (list);
	if (list->line[i])
	{
		j = 0;
		while (list->line[i + j] && list->line[i + j] != '$')
			j++;
		if ((int)ft_strlen(list->line) == j)
			return (list);
		result = ft_substr(list->line, 0, j);
		i += j;
		j = 0;
		while (list->line[i + j] && list->line[i + j] != ' ' && list->line[i + j] != '\\' && list->line[i + j] != '\'' && list->line[i + j] != '\"')
			if (list->line[i + ++j] == '$')
				break ;
		temp = ft_substr(list->line, i + 1, j);
		if (temp)
		{
			expand = ft_get_env_key(env, temp);
			free(temp);
		}
		else
		{
			temp = ft_strjoin("$", temp);
			expand = temp;
		}
		if (expand)
		{
			result = ft_strjoin(result, expand);
			free(expand);
		}
		result = ft_strjoin(result, &list->line[i + j]);
		free(list->line);
		list->line = result;
		ft_expand(list, env);
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
		if (list->line[j] == '\"')
		{
			temp = ft_substr(list->line, 0, j);
			temp = ft_strjoin(temp, &list->line[j + 1]);
			free(list->line);
			list->line = temp;
			while (list->line[j])
			{
				if (list->line[j] == '\'')
				{
					while (list->line[j + 1] && list->line[j + 1] != '\'')
					{
						if (list->line[j] == '$')
						{
							while (list->line[j] && (list->line[j] != '\"' && list->line[j] != ' '))
								j++;
						}
						else
						{
							temp = ft_strjoin(ft_substr(list->line, 0, j), "\\");
							temp = ft_strjoin(temp, &list->line[j]);
							free(list->line);
							list->line = temp;
							j++;
						}
						j++;
					}
				}
				else if (list->line[j] == '$')
				{
					while (list->line[j] && (list->line[j] != '\"' && list->line[j] != ' '))
						j++;
				}
				else
				{
					temp = ft_strjoin(ft_substr(list->line, 0, j), "\\");
					temp = ft_strjoin(temp, &list->line[j]);
					free(list->line);
					list->line = temp;
					j++;
				}
				j++;
			}
		}
		j++;
		if (list->line[j] == '\"')
		{
			temp = ft_substr(list->line, 0, j);
			temp = ft_strjoin(temp, &list->line[j + 1]);
			//printf("&ms->list->line[j + 1]:(%s)\n", &ms->list->line[j + 1]);
			free(list->line);
			list->line = temp;
		}
	}
	return (list);
}

static t_command **ft_split_line(t_command **list, char *line)
{
	int		i;
	int		total_split;
	char	**line_split;

	total_split = -1;
	line_split = ft_split(line, '|');
	if (!line_split)
		return (NULL);
	list = ft_calloc(total_split + 1, sizeof(t_command *));
	i = -1;
	while (line_split[++i])
	{
		list[i] = ft_calloc(1, sizeof(t_command));
		list[i]->line = line_split[i];
		if (i + 1 <= total_split)
			list[i]->next = list[i + 1];
		else
			list[i]->next = NULL;
	}
	return (list);
}

t_command	**ft_prompt(t_ms *g_ms)
{
	int		i;

	signal(SIGINT, ft_handler);
	rl_replace_line("", 0);
	if (g_ms->line)
		free(g_ms->line);
	g_ms->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!g_ms->line)
		return (NULL);
	//ms->list->line[ft_strlen(ms->list->line) + 1] = 0;
	if (!ft_is_empty(g_ms->line))
		add_history(g_ms->line);
	g_ms->list = ft_split_line(g_ms->list, g_ms->line);
	if (!g_ms->list)
		return (NULL);
	i = 0;
	while (g_ms->list[i])
	{
		g_ms->list[i] = ft_comillas(g_ms->list[i]);
		g_ms->list[i] = ft_expand(g_ms->list[i], g_ms->env);
		printf("g_ms->list[%d]->line:(%s)\n",i ,g_ms->list[i]->line);
		i++;
	}
	return (g_ms->list);
}
