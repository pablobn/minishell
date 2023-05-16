#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}
