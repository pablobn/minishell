#include "minishell.h"

extern t_ms *g_ms;

static char	*ft_get_cmd(char *str, char *path)
{
	char		**cases;
	char		*new;
	char		*tmp;
	int			i;

	if (access(str, X_OK) == 0)
		return (ft_strdup(str));
	cases = ft_split(path, ':');
	i = 0;
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

void	ft_execute_command(t_command *list, t_env *env)
{
	char	*path;
	char	*cmd_path;

	path = ft_get_env_key(env, "PATH");
	if (!path)
	{
		ft_putstr_fd("No existe PATH\n", 2);
		exit (127);
	}
	cmd_path = ft_get_cmd(list->flags[0], path);
	if (!cmd_path)
	{
		free(path);
		perror(list->flags[0]);
		exit (127);
	}
	free(path);
	if (execve(cmd_path, list->flags, ft_get_envp(env)) == -1)
	{
		perror(cmd_path);
		exit(-1);
	}
}

void	ft_pipex(t_command *list, t_env *env, t_ms *ms)
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
		if (!ft_check_built_in(list))
			ft_execute_command(list, env);
		else
			exit (ft_built_in(list, ms));
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
	int		num;

	pid = fork();
	if (pid != 0)
		g_ms->pid = pid;
	if (pid == 0)
	{
		while (list->next)
		{
			ft_pipex(list, ms->env, ms);
			list = list->next;
		}
		if (list->in != STDIN_FILENO)
			dup2(list->in, STDIN_FILENO);
		if (list->out != STDOUT_FILENO && list->out != 0)
			dup2(list->out, STDOUT_FILENO);
		if (!ft_check_built_in(list))
			ft_execute_command(list, ms->env);
		else
			exit (ft_built_in(list, ms));
	}
	wait(&num);
	if (WIFEXITED(num))
		ms->status = WEXITSTATUS(num);
	return (0);
}

void	ft_create_heredoc(t_command *list)
{
	int		file;
	char	*str;
	size_t	size;

	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (file < 0)
	{
		ft_putstr_fd("Error creando archivo here_doc", 2);
		exit (255);
	}
	while (1)
	{
		size = ft_strlen(list->heredoc);
		ft_putstr_fd("heredoc> ", 1);
		str = get_next_line(0);
		if (ft_strlen(str) - 1 > size)
			size = ft_strlen(str) - 1;
		if (ft_strncmp(str, list->heredoc, size) == 0)
			break ;
		write(file, str, ft_strlen(str));
	}
	free(str);
	close(file);
	list->in = open(".here_doc", O_RDONLY);
	if (list->in < 0)
	{
		unlink(".here_doc");
		ft_putstr_fd("Error abriendo archivo here_doc", 2);
		exit (255);
	}
}

int	ft_execute_line(t_ms *ms)
{
	t_command	*list;


	list = ms->list[0];
	if (list->heredoc)
		ft_create_heredoc(list);
	if (!list->next)
	{
		ft_built_in_cd(list, ms);
		if (ft_check_built_in_cd(list))
			list = list->next;
		else
			return (ft_start_pipex(list, ms));
	}
	else
		return (ft_start_pipex(list, ms));
	return (0);
}
