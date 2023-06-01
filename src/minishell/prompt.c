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
	rl_replace_line("", 0);
	if (cmd->line)
		free(cmd->line);
	cmd->line = readline(GREEN "minishell" BLUE "$" RESET " ");
	if (!cmd->line)
		return ;
	cmd->line[ft_strlen(cmd->line) + 1] = 0;
	if (!ft_is_empty(cmd->line))
		add_history(cmd->line);
}
