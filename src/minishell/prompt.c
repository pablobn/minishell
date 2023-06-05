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
		result = ft_substr(ms->list->line, 0, i + j);
		i += j;
		j = 0;
		while (ms->list->line[i + j] && ms->list->line[i + j] != ' ')
			j++;
		temp = ft_substr(ms->list->line, i + 1, j - 1);
		i += j;
		expand = ft_get_env_key(ms->env, temp);
		free(temp);
		if (expand)
			result = ft_strjoin(result, expand);
		result = ft_strjoin(result, &ms->list->line[i]);
		free(ms->list->line);
		ms->list->line = result;
		ft_expand(ms, i);
	}
	return (1);
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
	ms->list->line[ft_strlen(ms->list->line) + 1] = 0;
	if (!ft_is_empty(ms->list->line))
		add_history(ms->list->line);
	ft_expand(ms, 0);
}
