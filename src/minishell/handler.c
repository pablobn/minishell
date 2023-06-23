#include "minishell.h"
extern t_ms *g_ms;

void	ft_handler(int sig)
{
	// struct termios	old_termios;
	// struct termios	new_termios;

	// tcgetattr(STDIN_FILENO, &old_termios);
	// new_termios = old_termios;
	// new_termios.c_lflag &= ~ECHO;
	// tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	// tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	(void) sig;
	
	if (g_ms->pid != 0 && g_ms->pid != -1)
	{
		kill(g_ms->pid, SIGKILL);
		g_ms->pid = 0;
		rl_replace_line("  \n", 0);
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
