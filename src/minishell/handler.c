#include "minishell.h"

extern t_ms *g_ms;

void	ft_handler(int sig)
{
	(void) sig;
	if (g_ms->pid != 0 && g_ms->pid != -1)
	{
		printf("\n");
		kill(g_ms->pid, SIGKILL);
		g_ms->status = 130;
		g_ms->pid = 0;
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("  \n", 0);
		rl_redisplay();
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
