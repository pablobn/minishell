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

void	ft_prompt(t_command *cmd)
{
	signal(SIGINT, ft_handler);
	cmd->command = readline(GREEN "minishell" RED "$" RESET " ");
	if (!cmd->command)
		return ;
	if (!ft_is_empty(cmd->command))
		add_history(cmd->command);
}
