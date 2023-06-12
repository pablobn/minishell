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

static char	*ft_expand(char *line, t_env *env)
{
	int		j;
	char	*temp;
	char	*expand;
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (!env || !line)
		return (line);
	if (line[i])
	{
		j = 0;
		while (line[i + j] && line[i + j] != '$')
			j++;
		if ((int)ft_strlen(line) == j)
			return (line);
		result = ft_substr(line, 0, j);
		i += j;
		j = 0;
		while (line[i + j] && line[i + j] != ' ' && line[i + j] != '\\' && line[i + j] != '\'' && line[i + j] != '\"')
			if (line[i + ++j] == '$')
				break ;
		temp = ft_substr(line, i + 1, j);
		if (temp)
		{
			//printf("temp:(%s)\n", temp);
			expand = ft_get_env_key(env, temp);
			free(temp);
		}
		else
		{
			temp = ft_strjoin("$", temp);
			expand = temp;
		}
		if (expand)
			result = ft_strjoin(result, expand);
		result = ft_strjoin(result, &line[i + j]);
		free(line);
		line = result;
		ft_expand(line, env);
	}
	return (line);
}

static char	*ft_comillas(t_ms *ms)
{
	int		j;
	char	*temp;

	j = 0;
	while (ms->list->line[j])
	{
		if (ms->list->line[j] == '\"')
		{
			temp = ft_substr(ms->list->line, 0, j);
			temp = ft_strjoin(temp, &ms->list->line[j + 1]);
			free(ms->list->line);
			ms->list->line = temp;
			while (ms->list->line[j])
			{
				if (ms->list->line[j] == '\'')
				{
					while (ms->list->line[j + 1] && ms->list->line[j + 1] != '\'')
					{
						if (ms->list->line[j] == '$')
						{
							while (ms->list->line[j] && (ms->list->line[j] != '\"' && ms->list->line[j] != ' '))
								j++;
						}
						else
						{
							temp = ft_strjoin(ft_substr(ms->list->line, 0, j), "\\");
							temp = ft_strjoin(temp, &ms->list->line[j]);
							free(ms->list->line);
							ms->list->line = temp;
							j++;
						}
						j++;
					}
				}
				else if (ms->list->line[j] == '$')
				{
					while (ms->list->line[j] && (ms->list->line[j] != '\"' && ms->list->line[j] != ' '))
						j++;
				}
				else
				{
					temp = ft_strjoin(ft_substr(ms->list->line, 0, j), "\\");
					temp = ft_strjoin(temp, &ms->list->line[j]);
					free(ms->list->line);
					ms->list->line = temp;
					j++;
				}
				j++;
			}
		}
		j++;
		if (ms->list->line[j] == '\"')
		{
			temp = ft_substr(ms->list->line, 0, j);
			temp = ft_strjoin(temp, &ms->list->line[j + 1]);
			//printf("&ms->list->line[j + 1]:(%s)\n", &ms->list->line[j + 1]);
			free(ms->list->line);
			ms->list->line = temp;
		}
	}
	return (ms->list->line);
}

void	ft_prompt(t_ms *ms)
{
	signal(SIGINT, ft_handler);
	rl_replace_line("", 0);
	if (ms->list->line)
		free(ms->list->line);
	ms->list->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!ms->list->line)
		return ;
	//ms->list->line[ft_strlen(ms->list->line) + 1] = 0;
	if (!ft_is_empty(ms->list->line))
		add_history(ms->list->line);
	
	ms->list->line = ft_comillas(ms);
	ms->list->line = ft_expand(ms->list->line, ms->env);
}
