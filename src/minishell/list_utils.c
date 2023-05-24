#include "minishell.h"

int	ft_size_list(t_command *list)
{
	int	i;
	i = 1;
	while (list->next)
	{
		list = list->next;
		i++;
	}	
	return (i);
}
