#include "minishell.h"

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
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	ft_prompt(void)
{
	signal(SIGINT, ft_handler);
	g_cmd.command = readline(GREEN "minishell" RED "$" RESET " ");
	add_history(g_cmd.command);
}

//atexit(ft_leaks);


int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	while (42)
	{
		ft_prompt();
		if (!g_cmd.command)
			return (0);
	}
	return (0);
}
