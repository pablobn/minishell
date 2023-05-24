#include "minishell.h"

void	ft_give_value(t_command *a)
{
	// t_command	b;
	char **first;
	first = malloc(sizeof(char *) * 3);
	first[0] = "ls";
	first[1] = "-l";
	first[2] = NULL;
	// char *second[] = {"wc", "-l"};
	// b.command = "wc";
	// b.next = NULL;
	// b.back = a;
	// b.flags = second;
	a->command = "ls";
	a->next = NULL;
	a->back = NULL;
	a->out = STDOUT_FILENO;
	a->in = STDIN_FILENO;
	a->flags = first;
}

static char	*ft_get_cmd(char *str, char *path)
{
	char	**cases;
	char	*tmp;
	int		i;

	cases = ft_split(path, ':');
	i = 0;
	while (cases[i])
	{
		tmp = ft_strjoin(cases[i], str);
		if (access(tmp, 0) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_execute_command(t_command *list, char **envp)
{
	char *path;
	char *cmd_path;

	path = getenv("PATH");
	cmd_path = ft_get_cmd(ft_strjoin("/", list->command), path);
	if (!cmd_path)
		exit(1);
	execve(cmd_path, list->flags, envp);
}

// void	ft_pipex(t_command *list)
// {
// 	int	tube[2];
// 	pid_t pid;

// 	pipe(tube);

// }

int	ft_execute_line(t_ms *ms)
{
	t_command	*list;
	pid_t		pid;
	int			j;

	pid = fork();
	if (pid == 0)
	{
		list = ms->list;
		ft_give_value(list);
		// dup2(list->out, STDOUT_FILENO);
		// dup2(list->in, STDIN_FILENO);
		j = 0;
		while (list->next)
		{
			// ft_pipex(list);
			list = list->next;
			j++;
		}
		ft_execute_command(list, ms->envp);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
