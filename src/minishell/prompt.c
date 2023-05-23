#include "minishell.h"

void	ft_prompt(void)
{
	signal(SIGINT, ft_handler);
	g_cmd.command = readline(GREEN "minishell" RED "$" RESET " ");
	if ()
		add_history(g_cmd.command);
}

static int	ft_is_empty(char *str)
{
	int i;

}
