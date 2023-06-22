#include "minishell.h"

int	ft_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}
