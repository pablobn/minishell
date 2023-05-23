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

void	ft_prompt(void)
{
	signal(SIGINT, ft_handler);
	g_cmd.command = readline(GREEN "minishell" RED "$" RESET " ");
	if (!g_cmd.command)
			return ;
	if (!ft_is_empty(g_cmd.command))
		add_history(g_cmd.command);
}
