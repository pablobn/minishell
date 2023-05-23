#include "minishell.h"

void	ft_list_back(void)
{
	while (!g_cmd.back)
		g_cmd = *g_cmd.back;
}

void	ft_list_next(void)
{
	while (!g_cmd.next)
		g_cmd = *g_cmd.next;
}

int	ft_size_list(void)
{
	int	i;

	ft_list_back();
	i = 0;
	while (g_cmd.next)
		i++;
	return (0);
}
