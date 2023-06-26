#include "minishell.h"

extern t_ms	*g_ms;

static void	exit_child_process(t_command *list, t_ms *ms)
{
	if (!ft_check_built_in(list))
		ft_execute_command(list, ms->env);
	else
		exit (ft_built_in(list, ms));
}

void	ft_pipex(t_command *list, t_ms *ms)
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
		exit_child_process(list, ms);
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
			ft_pipex(list, ms);
			list = list->next;
		}
		if (list->in != STDIN_FILENO)
			dup2(list->in, STDIN_FILENO);
		if (list->out != STDOUT_FILENO && list->out != 0)
			dup2(list->out, STDOUT_FILENO);
		exit_child_process(list, ms);
	}
	wait(&num);
	if (WIFEXITED(num))
		ms->status = WEXITSTATUS(num);
	return (0);
}
