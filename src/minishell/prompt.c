#include "minishell.h"

t_ms	*g_ms;

static int	ft_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}

static char	*ft_expand(t_env *env, char *line)
{
	int		j;
	int		i;
	char	*temp;
	char	*expand;
	char	*result;

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
		ft_expand(env, line);
	}
	return (line);
}

static char	*ft_comillas(char *line)
{
	int		j;
	char	*temp;

	j = 0;
	while (line && line[j])
	{
		if (line[j] == '\"')
		{
			temp = ft_substr(line, 0, j);
			temp = ft_strjoin(temp, &line[j + 1]);
			free(line);
			line = temp;
			while (line[j])
			{
				if (line[j] == '\'')
				{
					while (line[j + 1] && line[j + 1] != '\'')
					{
						if (line[j] == '$')
						{
							while (line[j] && (line[j] != '\"' && line[j] != ' '))
								j++;
						}
						else
						{
							temp = ft_strjoin(ft_substr(line, 0, j), "\\");
							temp = ft_strjoin(temp, &line[j]);
							free(line);
							line = temp;
							j++;
						}
						j++;
					}
				}
				else if (line[j] == '$')
				{
					while (line[j] && (line[j] != '\"' && line[j] != ' '))
						j++;
				}
				else
				{
					temp = ft_strjoin(ft_substr(line, 0, j), "\\");
					temp = ft_strjoin(temp, &line[j]);
					free(line);
					line = temp;
					j++;
				}
				j++;
			}
		}
		j++;
			if (line[j] == '\"')
			{
				temp = ft_substr(line, 0, j);
				temp = ft_strjoin(temp, &line[j + 1]);
				free(line);
				line = temp;
			}
	}
	return (line);
} 

static t_command	*ft_pipe_split(t_ms *g_ms)
{
	char	**pipe_line;
	int		i;

	pipe_line = ft_split(g_ms->line, '|');
	g_ms->list = ft_calloc(1, sizeof(t_command *));
	if (!g_ms->list)
		return (NULL);
	i = 0;
	while (pipe_line[i])
	{
		g_ms->list[i] = *(t_command*)ft_calloc(1, sizeof(t_command));
		if (!&g_ms->list[i])
			return (NULL);
		g_ms->list[i].line = pipe_line[i];
		if (pipe_line[i + 1])
			g_ms->list[i].next = &g_ms->list[i + 1];
		else
			g_ms->list[i].next = NULL;
		i++;
	}
	free(g_ms->line);
	return (g_ms->list);
}

t_ms	*ft_prompt(t_ms *g_ms)
{
	int	count_p;
	printf("Entro\n");
	signal(SIGINT, ft_handler);
	rl_replace_line("", 0);
	if (g_ms->line)
		free(g_ms->line);
	g_ms->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!g_ms->line)
		return (NULL);
	if (!ft_is_empty(g_ms->line))
		add_history(g_ms->line);
	g_ms->list = ft_pipe_split(g_ms);
	count_p = 0;
	while (&g_ms->list[count_p])
	{
		printf("g_ms->list[count_p].line:(%s)\n", g_ms->list[count_p].line);
		g_ms->list[count_p].line = ft_comillas(g_ms->list[count_p].line);
		g_ms->list[count_p].line = ft_expand(g_ms->env, g_ms->list[count_p].line);
		count_p++;
	}
	printf("salgo\n");
	return (g_ms);
}
