#include "minishell.h"

int	ft_size_list(t_command *list)
{
	int	i;

	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}	
	return (i);
}

int	ft_size_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
