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

static int	ft_expand(t_ms *ms)
{
	int		i;
	int		j;
	char	*temp;
	char	*expand;

	i = 0;
	if (!ms->env || !ms->list->line)
		return (0);
	while (ms->list->line[i])
	{
		j = 0;
		while (ms->list->line[i + j] && ms->list->line[i + j] != '$')
			j++;
		temp = ft_substr(ms->list->line, i, j);
		printf("temp:(%s)\n", temp);
		i += j + 1;
		j = 0;
		while (ms->list->line[i + j] && !ft_isalnum(ms->list->line[i + j]))
			j++;
		expand = ft_substr(ms->list->line, i, j);
		printf("expand:(%s)\n", expand);
		i += j;
		sleep(2);
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
	ft_expand(ms);
}
