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

int	ft_space_iter(char *str, int i)
{
	if (!str)
		return (i);
	while (str[i] && str[i] == ' ' && (i - 1 >= -1 || str[i - 1] == '\\'))
		i++;
	return (i);
}