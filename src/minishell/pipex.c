#include "minishell.h"

static char	*ft_get_cmd(char *str, char *path)
{
	char		**cases;
	char		*new;
	char		*tmp;
	struct stat	file_stat;
	int			i;

	cases = ft_split(path, ':');
	i = 0;
	if (stat(str, &file_stat) != 0)
	{
		if (access(str, X_OK) == 0)
			return (ft_strdup(str));
	}
	new = ft_strjoin("/", str);
	while (cases[i])
	{
		tmp = ft_strjoin(cases[i], new);
		if (access(tmp, X_OK) == 0)
			return (free(new), tmp);
		free(tmp);
		i++;
	}
	return (free(new), ft_free_matrix(cases), NULL);
}

int	ft_execute_command(t_command *list, t_env *env)
{
	char	*path;
	char	*cmd_path;

	path = ft_get_env_key(env, "PATH");
	if (!path)
	{
		ft_putstr_fd("No existe PATH", 2);
		exit(1);
	}
	cmd_path = ft_get_cmd(list->flags[0], path);
	if (!cmd_path)
	{
		perror(list->flags[0]);
		exit (1);
	}
	return (execve(cmd_path, list->flags, ft_get_envp(env)));
}

void	ft_pipex(t_command *list, t_env *env)
{
	pid_t	pid;
	int		tube[2];

	pipe(tube);
	pid = fork();
	if (pid == 0)
	{
		close(tube[0]);
		if (list->in != STDIN_FILENO)
			dup2(list->in, STDIN_FILENO);
		if (list->out != STDOUT_FILENO && list->out != 0)
			dup2(list->out, STDOUT_FILENO);
		else
			dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
		if (ft_execute_command(list, env) < 0)
			perror(list->flags[0]);
	}
	else
	{
		wait(NULL);
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}
}

int	ft_start_pipex(t_command *list, t_ms *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!list->next)
		{
			if (list->in != STDIN_FILENO)
				dup2(list->in, STDIN_FILENO);
			if (list->out != STDOUT_FILENO && list->out != 0)
				dup2(list->out, STDOUT_FILENO);
		}
		while (list->next)
		{
			ft_pipex(list, ms->env);
			list = list->next;
		}
		if (ft_execute_command(list, ms->env) < 0)
			perror(list->flags[0]);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_execute_line(t_ms *ms)
{
	t_command	*list;

	list = ms->list[0];
	ft_built_in(list, ms);
	if (ft_check_built_in(list))
	{
		if (!list->next)
			return (0);
		list = list->next;
	}
	else
		ft_start_pipex(list, ms);
	return (0);
}
