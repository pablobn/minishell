#include "minishell.h"

int	ft_size_list(t_command *list)
{
	int	i;

	i = 0;
	while (list->next)
		i++;
	return (0);
}
