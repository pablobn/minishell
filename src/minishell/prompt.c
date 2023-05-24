#include "minishell.h"

extern t_ms *g_ms;

static int	ft_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}

void	ft_prompt(void)
{
	signal(SIGINT, ft_handler);
	g_ms->list->command = readline(GREEN "minishell" RED "$" RESET " ");
	if (!g_ms->list->command)
		return ;
	if (!ft_is_empty(g_ms->list->command))
		add_history(g_ms->list->command);
}
