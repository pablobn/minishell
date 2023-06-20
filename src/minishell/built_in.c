#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("Error al obtener el directorio de trabajo actual");
		exit(1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	ft_echo(t_command *list)
{
	int	i;

	i = 1;
	while (list->flags[i])
	{
		printf("%s", list->flags[i]);
		if (list->flags[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}

int	ft_built_in(t_command *list, t_ms *ms)
{
	if (ft_strncmp(list->flags[0], "export", 6) == 0)
		return (ft_export(ms, list->flags[1]));
	if (ft_strncmp(list->flags[0], "unset", 5) == 0)
		return (ft_unset(ms, list->flags[1]));
	if (ft_strncmp(list->flags[0], "pwd", 5) == 0)
		return (ft_pwd());
	if (ft_strncmp(list->flags[0], "echo", 5) == 0)
		return (ft_echo(list));
	return (0);
}

int	ft_built_in_cd(t_command *list, t_ms *ms)
{
	if (ft_strncmp(list->flags[0], "cd", 2) == 0)
		return (ft_cd(list, ms));
	return (0);
}

int	ft_check_built_in_cd(t_command *list)
{
	if (ft_strncmp(list->flags[0], "cd", 2) == 0)
		return (1);
	return (0);
}

int	ft_check_built_in(t_command *list)
{
	if (ft_strncmp(list->flags[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "unset", 5) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "pwd", 5) == 0)
		return (1);
	if (ft_strncmp(list->flags[0], "echo", 5) == 0)
		return (1);
	return (0);
}
