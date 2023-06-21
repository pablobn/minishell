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
	// pid_t pgid = getpgid(0);
	// printf("Soy el proceso padre %d\n", getpid());
	// printf("SOY EL PROCESO HIJO %d\n", pgid);
	rl_replace_line("  \n", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
