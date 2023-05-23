#include "minishell.h"

void	ft_prompt(void)
{
	signal(SIGINT, ft_handler);
	g_cmd.command = readline(GREEN "minishell" RED "$" RESET " ");
	add_history(g_cmd.command);
}
