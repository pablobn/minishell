#include "minishell.h"

t_command	cmd;

void	ft_prompt(void)
{
	struct termios	old_termios;
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	cmd.command = readline(GREEN "minishell" RED "$" RESET " ");
	add_history(cmd.command);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

//atexit(ft_leaks);

void	ft_handler(int sig)
{
	(void) sig;
	ft_prompt();
}

int	main(int argc, char **argv, char **envp)
{

	signal(SIGINT, ft_handler);
	(void) argc;
	(void) argv;
	(void) envp;
	while (42)
	{
		ft_prompt();
		if (!cmd.command)
			return (0);
	}
	return (0);
}
