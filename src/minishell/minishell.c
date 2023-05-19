#include "minishell.h"

void	ft_prompt(t_command *cmd)
{
	cmd->command = readline(GREEN "minishell" RED "$" RESET " ");
}

//atexit(ft_leaks);

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;

	(void) argc;
	(void) argv;
	(void) envp;
	while (42)
	{
		ft_prompt(&cmd);
		if (!cmd.command)
			return (0);
	}
	return (0);
}
