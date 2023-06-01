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

// static int	ft_expand(t_ms *ms)
// {
// 	if (!ms->env)
		
// }

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
	//ft_expand(ms);
}
