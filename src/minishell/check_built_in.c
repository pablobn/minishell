#include "minishell.h"

int	ft_check_built_in_cd(t_command *list)
{
	if (ft_strncmp(list->flags[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "unset", 5) == 0)
		return (1);
	if (list->flags[1])
	{
		if (ft_strncmp(list->flags[0], "export", 6) == 0)
			return (1);
	}
	return (0);
}

int	ft_check_built_in(t_command *list)
{
	if (ft_strncmp(list->flags[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "pwd", 5) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "echo", 5) == 0)
		return (1);
	return (0);
}
