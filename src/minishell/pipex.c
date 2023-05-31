#include "minishell.h"

void	ft_give_value(t_command *a)
{
	t_command	*b;
	char		**first;
	char		**second;

	b = ft_calloc(1, sizeof(t_command));
	first = ft_calloc(3, sizeof(char *));
	first[0] = "ls";
	first[1] = "-l";
	first[2] = NULL;
	second = ft_calloc(3, sizeof(char *));
	second[0] = "wc";
	second[1] = "-l";
	second[2] = NULL;
	b->cmd = "wc";
	b->next = NULL;
	b->back = a;
	b->out = STDOUT_FILENO;
	b->in = STDIN_FILENO;
	b->flags = second;
	a->cmd = "ls";
	a->next = b;
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
	char	*path;
	char	*cmd_path;

	path = getenv("PATH");
	cmd_path = ft_get_cmd(ft_strjoin("/", list->cmd), path);
	if (!cmd_path)
		exit (1);
	execve(cmd_path, list->flags, envp);
}

void	ft_pipex(t_command *list, char **envp)
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
		if (list->out != STDOUT_FILENO)
			dup2(list->out, STDOUT_FILENO);
		else
			dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
		ft_execute_command(list, envp);
	}
	else
	{
		wait(NULL);
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}
}

int	ft_execute_line(t_ms *ms)
{
	t_command	*list;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		list = ms->list;
		ft_give_value(list);
		while (list->next)
		{
			ft_pipex(list, ms->envp);
			list = list->next;
		}
		ft_execute_command(list, ms->envp);
	}
	waitpid(pid, NULL, 0);
	return (0);
}